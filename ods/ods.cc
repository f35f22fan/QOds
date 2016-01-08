/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "Book.hpp"
#include "Cell.hpp"
#include "CellRef.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "Row.hpp"
#include "Sheet.hpp"

#include <QDebug>
#include <QString>
#include <QMap>
#include <QXmlStreamWriter>

#include <math.h>

namespace ods	{ // ods::

QChar
CharFromOp(const ods::Op op)
{
	switch (op) {
	case ods::Op::Mult:		return '*';
	case ods::Op::Divide:	return '/';
	case ods::Op::Add:		return '+';
	case ods::Op::Subtract:	return '-';
	default:				return '?';
	}
}

ods::Op
CharToOp(const QChar c)
{
	if (c == '*')
		return ods::Op::Mult;
	if (c == '/')
		return ods::Op::Divide;
	if (c == '+')
		return ods::Op::Add;
	if (c == '-')
		return ods::Op::Subtract;
	return ods::Op::None;
}

ods::Cell*
FindCell(ods::CellRef *ref, ods::Cell *source)
{
	ods::Sheet *sheet = ref->sheet();
	if (sheet == nullptr)
		sheet = source->row()->sheet();
	auto *row = sheet->row(ref->row());
	if (row == nullptr)
	{
		mtl_qline(QStringLiteral("No such row: ") + QString::number(ref->row())
			+ QStringLiteral(", row count: ")
			+ QString::number(sheet->CalcRowCount()));
		return nullptr;
	}
	
	auto *cell = row->cell(ref->col());
	if (cell == nullptr)
	{
		mtl_qline(QStringLiteral("No such cell: ") + QString::number(ref->col())
			+ QStringLiteral(" at row: ") + QString::number(ref->row())
			+ QStringLiteral(", column count: ")
			+ QString::number(row->column_count()));
		return nullptr;
	}
	return cell;
}

QString
FontSizeToString(const double size, const ods::FontSizeType size_type)
{
	QString str = QString::number(size);
	if (size_type == ods::FontSizeType::Pt)
		str += "pt";
	else if (size_type == ods::FontSizeType::Cm)
		str += "cm";
	else if (size_type == ods::FontSizeType::In)
		str += "in";
	return str;
}

qint32
ColumnLettersToNumber(const QStringRef &letters)
{
	const auto char_A_code = QChar('A').unicode();
	qint32 col = 0;
	const int kCount = letters.size();
	for (int j = 0; j < kCount; j++)
	{
		const int kDiff = letters.at(j).unicode() - char_A_code;
		if (kCount - 1 == j)
			col += kDiff;
		else
			col += pow(26, kCount - j - 1) * (kDiff+1);
	}
	
	return col;
}

QString
ColumnNumberToLetters(const qint32 column)
{
	if (column < 0)
		return QStringLiteral("");
	qint32 digit_count = 1;
	qint32 offset = 0;
	// 26 => alphabet size
	for (qint32 top = 26; column >= top + offset; top *= 26)
	{
		offset += top;
		++digit_count;
	}
	
	QString ret;
	qint32 col = column - offset;
	const auto kCharACode = QChar('A').unicode();
	while (digit_count > 0)
	{
		QChar c(kCharACode + (col % 26));
		ret.prepend(c);
		--digit_count;
		col /= 26;
	}
	return ret;
}

ods::CellRef*
CreateCellRef(const QStringRef &full_cell_name, ods::Book *book)
{
	int index = full_cell_name.indexOf('.');
	// example: table:formula="of:=[.A1]+[Sheet2.A1]"
	QStringRef cell_name = full_cell_name.right(full_cell_name.size() - 1 - index);
	const bool current_sheet = index == 0;
	QString sheet_name;
	auto *cell_ref = new ods::CellRef();

	if (!current_sheet)
	{
		sheet_name = full_cell_name.left(index).toString();
		cell_ref->sheet_set(book->sheet(sheet_name));
	} else {
		sheet_name = ".";
	}

	/**
	qDebug() << SRC_FILE_NAME << ", full cell name:" << full_cell_name
		<< ", cell name:" << cell_name <<
		", sheet_name:" << sheet_name;
	**/
	
	const int count = cell_name.size();
	
	for(int i = 0; i < count; i++)
	{
		QChar c = cell_name.at(i);

		if (!c.isDigit())
			continue;
		QStringRef letters = cell_name.left(i);
		cell_ref->col_set(ods::ColumnLettersToNumber(letters));
		QStringRef digits = cell_name.right(count - i);
		bool ok;
		cell_ref->row_set(digits.toInt(&ok));

		if (ok) {
			cell_ref->row_set(cell_ref->row() - 1);
			break;
		} else {
			delete cell_ref;
			return nullptr;
		}
	}
	return cell_ref;
}

ods::Type
TypeFromString(const QString &value_type)
{
	if (value_type.size() == 0)
		return ods::Type::NotSet;
	if (value_type == ods::ns::kDouble)
		return ods::Type::Double;
	if (value_type == ods::ns::kString)
		return ods::Type::String;
	if (value_type == ods::ns::kCurrency)
		return ods::Type::Currency;
	if (value_type == ods::ns::kPercentage)
		return ods::Type::Percentage;
	if (value_type == ods::ns::kDate)
		return ods::Type::Date;
	if (value_type == ods::ns::kTime)
		return ods::Type::Duration;
	if (value_type == ods::ns::kBool)
		return ods::Type::Bool;
	return ods::Type::NotSet;
}

const char*
TypeToString(const ods::Type &value_type)
{
	switch (value_type)
	{
	case ods::Type::Double: return ods::ns::kDouble;
	case ods::Type::String: return ods::ns::kString;
	case ods::Type::Currency: return ods::ns::kCurrency;
	case ods::Type::Percentage: return ods::ns::kPercentage;
	case ods::Type::Date: return ods::ns::kDate;
	case ods::Type::Duration: return ods::ns::kTime;
	case ods::Type::Bool: return ods::ns::kBool;
	case ods::Type::NotSet: return "[Not set]";
	return "[Other]";
	}
}

quint32
version_major() { return 1; }

quint32
version_micro() { return 2; }

quint32
version_minor() { return 3; }

} // ods::



















