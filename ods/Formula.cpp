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

#include "Formula.hpp"

#include "Cell.hpp"
#include "ods.hh"
#include "Region.hpp"
#include "Row.hpp"
#include "Sheet.hpp"
#include "Value.hpp"

#include <QDebug>

namespace ods	{

Formula::Formula() :
	formula_(ods::kFormulaPrefix)
{
}

Formula::Formula(ods::Cell *cell, const QString &str) :
	source_(cell)
{
	formula_ = str.simplified().replace(" ", "");
}

Formula::~Formula()
{}

void
Formula::Add(ods::Cell *cell, ods::Sheet *sheet)
{
	if (sheet == nullptr)
		formula_ += QLatin1String("[.");
	else
		formula_ += QChar('[') + sheet->name() + QChar('.');
	formula_ += cell->Address();
	formula_ += QLatin1String("]");
}

void
Formula::Add(const ods::Grouping g)
{
	if (g == ods::Grouping::Open)
		formula_ += QChar('(');
	else
		formula_ += QChar(')');
}

void
Formula::Add(const ods::Op op)
{
	formula_ += ods::CharFromOp(op);
}

ods::Formula*
Formula::Clone()
{
	auto *formula = new ods::Formula();
	formula->formula_set(formula_);
	formula->source_set(source_);
	value_.CopyTo(formula->value());
	formula->error_set(error_);
	return formula;
}

//FIXME
bool
Formula::GetDouble(ods::CellRef *cell_ref, double &num)
{
	auto *found_cell = ods::FindCell(cell_ref, source_);
	if (found_cell == nullptr)
	{
		mtl_warn("Cell not found");
		return false;
	}
	if (found_cell->HasFormula())
	{
		const auto &value = found_cell->formula()->value();
		if (value.IsNotSet())
		{
			mtl_warn("No value");
		} else if (value.IsDouble() || value.IsCurrency()){
			num = *value.AsDouble();
			return true;
		} else {
			mtl_warn("Unknown value type");
		}
		return false;
	}
	bool ok;
	num = found_cell->value().toString().toDouble(&ok);
	return ok;
}

void
Formula::UpdateValue()
{
	/**
	((C5+B5)/A5)*(C4+B4*A3)+B3-C3
	((10+0.5)/3)*(4.5+2.4*22.3)+8-6
	**/
	value_.type_set(ods::Type::NotSet);
	error_.clear();
	if (!formula_.startsWith(ods::kFormulaPrefix))
	{
		error_ = QLatin1String("Doesn't start with ") + ods::kFormulaPrefix;
		return;
	}
	QString number_formula;
	QStringRef form = formula_.rightRef(formula_.size() -
		ods::kFormulaPrefix.size());
	double num;

	ods::Book *book = source_->row()->sheet()->book();

	for(int i = 0; i < form.size(); i++)
	{
		if (form.at(i) != '[')
		{
			number_formula.append(form.at(i));
			continue;
		}
		int bracket_end = form.indexOf(']', i + 1);
		if (bracket_end == -1)
			{
				error_ = QLatin1String("] not found");
				return;
			}
// FIXME: next line assumes a dot for current sheet name, hence
// table:formula="of:=[.A1]+[Sheet2.A1]" won't work
		QStringRef cell_name = form.mid(i + 1, bracket_end - i - 1);
		auto *cell_ref = ods::CreateCellRef(cell_name, book);
		if (cell_ref == nullptr)
		{
			error_ = QLatin1String("ReadRowCol() failed, cell_name: ") +
				cell_name.toString();
			return;
		}

		if (!GetDouble(cell_ref, num))
		{
			/**
			QString out_str = QStringLiteral("failed double(), row: ")
				+ QString::number(cell_ref->row)
				+ QStringLiteral(", col: ") + QString::number(cell_ref->col)
				+ QStringLiteral(", from cell_name: ")
				+ cell_name.toString();
			mtl_qline(out_str);
			**/
			error_ = QLatin1String("GetDouble() failed");
			return;
		}

		number_formula.append(QString::number(num));
		i = bracket_end;
	}
	auto *deepest = new ods::Region(number_formula);

	while (deepest->deep() >= 1)
	{
		deepest->Eval(value_);
		if (deepest->HasAnError())
		{
			error_ = deepest->error();
			return;
		}
		if (value_.IsNotSet())
		{
			error_ = QLatin1String("Region::Eval() error");
			delete deepest;
			return;
		}
		 
		if (value_.IsString() || value_.IsDate())
		{
			delete deepest;
			return;
		}

		if (!value_.IsDouble() && !value_.IsCurrency())
		{
			error_ = QLatin1String("Value not a number");
			delete deepest;
			return;
		}
		
		if (number_formula.size() == 0)
			break;
		QString str_num = QString::number(*value_.AsDouble());
		QString temp = number_formula.left(deepest->start_index());
		if (deepest->end_index() < number_formula.size()-1)
		{
			QString right = number_formula.right(number_formula.size()
				- deepest->end_index() - 1);
			temp += str_num + right;
		} else {
			temp += str_num;
		}
		number_formula = temp;
		delete deepest;
		deepest = new ods::Region(number_formula);
	}
	deepest->Eval(value_);
	delete deepest;
}

} // namespace ods
