/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Row.hpp"
#include "Attrs.hpp"
#include "Book.hpp"
#include "Cell.hpp"
#include "Column.hpp"
#include "Content.hpp"
#include "Node.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "Sheet.hpp"
#include "Style.hpp"
#include "style/style.hxx"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace ods	{

Row::Row(ods::Sheet *sheet, ods::Tag *tag, const qint32 row_start) :
	row_start_(row_start),
	sheet_(sheet),
	tag_(tag)
{
	Init();
}

Row::~Row()
{
	foreach (auto *cell, cells_)
		delete cell;
}

void
Row::AddColCount(ods::Cell *cell)
{
	qint32 add;
	if (cell->IsEmpty2() || cell->is_covered())
		add = cell->col_count();
	else
		add = 1;
	column_count_ += add;
}

ods::Cell*
Row::cell(const qint32 column)
{
	//if (column >= column_count_)
	//	return nullptr;
	foreach (auto *cell, cells_)
	{
		if (cell->UpToColumn() >= column)
			return cell;
	}
	return nullptr;
}

ods::Cell*
Row::CreateCell(const qint32 at_column)
{
	if (at_column < 0)
	{
		mtl_warn("at_column < 0");
		return nullptr;
	}
	
	if (at_column == 0)
		return InsertCell(0, false);
	
	auto *prev_cell = GetPrevCell(at_column);
	// stage: Null
	if (prev_cell == nullptr)
	{
		//insert placeholder with proper repeat_col
		InsertEmptyCell(0, at_column, false);
		return InsertCell(at_column);
	}
	
	// stage: Next to it
	const qint32 kPrevCellUpToCol = prev_cell->col_start();

	if (kPrevCellUpToCol + 1 == at_column) // is next to it
	{
		return InsertCell(at_column);
	}
	
	// stage: A gap between them
	if (prev_cell->IsEmpty2())
	{
		prev_cell->SetNumColsRepeated(at_column - prev_cell->col_start());
		return InsertCell(at_column);
	}
	quint16 placeholder_num_cols = at_column - 1 - kPrevCellUpToCol;
	const qint32 col_start = kPrevCellUpToCol + 1;
	const bool covered = prev_cell->col_count() > 1;
	InsertEmptyCell(col_start, placeholder_num_cols, covered);
	return InsertCell(at_column, false);
}

ods::Cell*
Row::GenCell(const qint32 at_column, const bool covered)
{
	ods::Tag *tag = nullptr;
	if (covered)
		tag = ods::tag::CoveredSheetCell(tag_->ns(), nullptr);
	else
		tag = ods::tag::SheetCell(tag_->ns(), nullptr);
	return new ods::Cell(this, tag, at_column);
}

ods::Cell*
Row::GetPrevCell(const qint32 at_column)
{
	ods::Cell *prev = nullptr;
	foreach (auto *cell, cells_)
	{
		if (cell->UpToColumn() >= at_column)
			return prev;
		prev = cell;
	}
	return prev;
}

void
Row::Init()
{
	auto *attrs = tag_->attrs();
	
	if (attrs != nullptr)
	{
		auto &ns = tag_->ns();
		auto *attr = attrs->Get(ns.sheet(), ods::ns::kNumRowsRepeated);
		if (attr != nullptr)
			attr->ToInt32(num_rows_repeated_);
	}
	
	column_count_ = 0;
	auto &subnodes = tag_->subnodes();
	
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag() || !node->Tag()->IsAnyCell())
			continue;
		
		auto *tag = node->Tag();
		auto *cell = new ods::Cell(this, tag, column_count_);
		cells_.append(cell);
		AddColCount(cell);
	}
}

void
Row::InitEnd()
{
	column_count_ = 0;
	foreach (ods::Cell *cell, cells_)
		AddColCount(cell);
//	qDebug() << "Row::InitEnd(): row at index " << row_start_ <<
//	"has " << column_count_ << "columns and " << cells_.size() <<
//	" cells";
	foreach (ods::Cell *cell, cells_)
		cell->InitEnd();
}

ods::Cell*
Row::InsertCell(const qint32 at_column, const bool covered)
{
	auto *cell = GenCell(at_column, covered);
	const int size = cells_.size();
	int index = 0;
	for (; index < size; ++index)
	{
		auto *item = cells_.at(index);
		if (item->UpToColumn() > at_column)
			break;
	}
	cells_.insert(index, cell);
	tag_->subnodes().insert(index, new ods::Node(cell->tag()));
	return cell;
}

ods::Cell*
Row::InsertEmptyCell(const qint32 at_column, const quint16 num_cols_repeated,
	const bool covered)
{
	auto *cell = InsertCell(at_column, covered);
	if (num_cols_repeated != 1)
		cell->SetNumColsRepeated(num_cols_repeated);
	return cell;
}

void
Row::PreSave(const qint32 total_cols)
{
	InitEnd();
	if (total_cols <= 0)
		return;
	const qint32 diff = total_cols - column_count_;
	if (diff < 1)
		return;
	// if last cell is a placeholder, increase its num_cols_repeated_
	if (cells_.size() > 0)
	{
		auto *cell = cells_.at(cells_.size() - 1);
		if (cell->IsEmpty2())
		{
			cell->SetNumColsRepeated(total_cols - cell->col_start());
			return;
		}
	}
	InsertEmptyCell(column_count_, diff, false);
}

void
Row::SetCoveredCellRange(ods::Cell *root_cell, const qint32 kColStart,
	const qint32 kColEnd)
{
	for (auto i = kColStart; i < kColEnd;)
	{
		auto *cov_cell = cell(i);
		if (cov_cell == nullptr)
		{
			auto num_cols_repeated = kColEnd - i + 1;
			InsertEmptyCell(i, num_cols_repeated, true);
			return;
		}
		if (cov_cell == root_cell)
		{
			i += cov_cell->col_count();
			continue;
		}
		const auto kCellEnd = i + cov_cell->col_count();
		if (kCellEnd == kColEnd)
		{
			cov_cell->SetCovered();
			return;
		}
		if (kCellEnd < kColEnd)
		{
			cov_cell->SetCovered();
			i += cov_cell->col_count();
			continue;
		}
		mtl_line("kCellEnd > kColEnd");
	}
}

void
Row::SetNumRowsRepeated(const qint32 num)
{
	tag_->AttrSet(tag_->ns().sheet(), ods::ns::kNumRowsRepeated,
		QString::number(num));
	num_rows_repeated_ = num;
}

void
Row::AdjustHeightBy(ods::Cell *cell)
{
	bool set_style = (opt_row_height_style_ == nullptr);
	
	if (set_style)
	{
		opt_row_height_style_ =	sheet_->book()->CreateStyle(
			ods::StyleFamilyId::Row, ods::StylePlace::ContentFile);
	}
	
	const int col_width_in_pixels = 60;
	int max_size = cell->ComputeHeightInPixels(col_width_in_pixels);
	
	if (max_size == -1)
	{
		mtl_line();
		if (set_style)
		{
			delete opt_row_height_style_;
			opt_row_height_style_ = nullptr;
		}
		return;
	}
	
	double total = max_size * 1.2 * ods::kInchesInAPoint;
	mtl_line("pixel/point size: %d, size in inches + adjustment: %f",
		max_size, total);
	
	opt_row_height_style_->SetOptimalRowHeight(total, ods::FontSizeType::In);
	
	if (set_style)
		SetStyle(opt_row_height_style_);
}

void
Row::SetOptimalHeightStyle()
{
	bool set_style = (opt_row_height_style_ == nullptr);
	
	if (set_style)
	{
		opt_row_height_style_ =	sheet_->book()->CreateStyle(
			ods::StyleFamilyId::Row, ods::StylePlace::ContentFile);
	}
	
	double max_size = 0.0;
	
	foreach (auto *cell, cells_)
	{
		auto *style = cell->style();
		
		if (style == nullptr)
			continue;
		
		if (style->font_size_type() == ods::FontSizeType::NotSet)
			continue;
		
		double d = style->FontSizeInInches();
		
		if (d > max_size)
			max_size = d;
	}
	
	if (max_size <= 0.0001)
	{
		if (set_style) // clean up if needed
		{
			delete opt_row_height_style_;
			opt_row_height_style_ = nullptr;
		}
		return;
	}
	
	opt_row_height_style_->SetOptimalRowHeight(max_size * 1.2,
		ods::FontSizeType::In);
	
	if (set_style)
		SetStyle(opt_row_height_style_);
}

void
Row::SetStyle(ods::Style *style)
{
	style_name_ = style->name();
	tag_->AttrSet(tag_->ns().sheet(), ods::style::kStyleName, style_name_);
}

void
Row::UpdateColIndices()
{
	qint32 col_start = 0;
	foreach (auto *cell, cells_) {
		cell->col_start_set(col_start);
		col_start += cell->col_count();
	}
}

} // namespace ods

