/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Sheet.hpp"
#include "Book.hpp"
#include "Column.hpp"
#include "Content.hpp"
#include "Node.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "Row.hpp"
#include "Style.hpp"
#include "style/style.hxx"
#include "style/tag.hh"
#include <QDebug>

namespace ods	{

Sheet::Sheet(ods::Content *content, ods::Tag *tag) :
	content_(content),
	tag_(tag)
{
	Init();
}

Sheet::~Sheet()
{
	foreach (auto row, rows_)
		delete row;
}

void
Sheet::AddColumnSpanUpTo(const int col_index)
{
	ods::Ns &ns = tag_->ns();
	auto *col_tag = ods::tag::SheetColumn(ns, nullptr);
	auto *column = new ods::Column(this, col_tag);
	column->SetNumColsRepeated(col_index - last_column_width_set_ - 1);
	
	auto *style = book()->CreateColumnStyle();
	
	auto *tag = style->GetTag(ods::style::tag::SheetColumnProps);
	tag->AttrSet(ns.fo(), ods::style::kBreakBefore, ods::ns::kAuto);
	column->SetStyle(style);
	
	style = content_->book()->CreateStyle(ods::StyleFamilyId::Cell);
//	style->SetFontName("Arial");
	col_tag->AttrSet(ns.sheet(), ods::style::kDefaultCellStyleName,
		style->name());
	
	auto &subnodes = tag_->subnodes();
	subnodes.append(new ods::Node(col_tag));
}

ods::Book*
Sheet::book()
{
	return content_->book();
}

qint32
Sheet::CalcRowCount()
{
	qint32 ret = 0;
	foreach (auto *row, rows_)
		ret += row->num_rows_repeated();
	return ret;
}

ods::Row*
Sheet::CreateRow(const qint32 at_row)
{
	if (at_row < 0) {
		mtl_warn("at_row < 0");
		return nullptr;
	}
	if (at_row == 0)
		return InsertRow(0);
	
	// stage: Null
	auto *prev_row = GetPrevRow(at_row);
	if (prev_row == nullptr) {
		//insert placeholder with proper repeat_row
		InsertPlaceholder(0, at_row);
		return InsertRow(at_row);
	}
	
	// stage: Next to it
	const qint32 kPrevRowUpToCol = prev_row->UpToRow();
	if (kPrevRowUpToCol + 1 == at_row) // is next to it
		return InsertRow(at_row);
	
	// stage: A gap between them
	if (prev_row->IsEmpty()) {
		prev_row->SetNumRowsRepeated(at_row - prev_row->row_start());
		return InsertRow(at_row);
	}
	
	qint32 placeholder_num_rows = at_row - 1 - kPrevRowUpToCol;
	qint32 row_start = kPrevRowUpToCol + 1;
	InsertPlaceholder(row_start, placeholder_num_rows);
	return InsertRow(at_row);
}

ods::Row*
Sheet::GetPrevRow(const qint32 at_row)
{
	ods::Row *prev = nullptr;
	
	foreach (auto *row, rows_)
	{
		if (row->UpToRow() >= at_row)
			return prev;
		prev = row;
	}
	
	return prev;
}

void
Sheet::Init()
{
	ods::Ns &ns = tag_->ns();
	ods::Attrs *attrs = tag_->attrs();
	
	if (attrs != nullptr)
	{
		auto *attr = attrs->Get(ns.sheet(), ods::ns::kName);
		if (attr != nullptr)
			name_ = attr->value();
	}
	
	qint32 row_start = 0;
	auto &subnodes = tag_->subnodes();
	
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag())
			continue;
		
		auto *tag = node->Tag();
		
		if (tag->IsRow())
		{
			auto *row = new ods::Row(this, tag, row_start);
			rows_.push_back(row);
			row_start += row->num_rows_repeated();
		} else if (tag->IsColumn()) {
			//@@Fix MS Office sometimes creates > 1 table:column tags
			// Not sure how to reproduce and whether still valid:
			//if (column_ == nullptr)
			//	column_ = new ods::Column(this, tag);
		}
	}
	//if (column_ == nullptr)
	//	InitDefault();
}

void
Sheet::InitDefault()
{
	//InitColumn();
	/**
	auto *style = book()->CreateStyle(ods::StyleFamilyId::Sheet,
		ods::StylePlace::StylesFile);
	auto *tag = style->GetSheetPropsTag();
	auto &ns = tag_->ns();
	tag->AttrSet(ns.sheet(), ods::style::kDisplay, ods::ns::kTrue);
	tag->AttrSet(ns.style(), ods::style::kWritingMode,
		ods::style::kWritingModeLrtb);
	SetStyle(style);
	**/
}

void
Sheet::InitEnd()
{
	foreach (auto *row, rows_)
		row->InitEnd();
	//InitColumn();
}

ods::Row*
Sheet::InsertPlaceholder(const qint32 at_row, const qint32 row_repeat)
{
	auto *row = InsertRow(at_row);
	row->SetNumRowsRepeated(row_repeat);
	return row;
}

ods::Row*
Sheet::InsertRow(const qint32 at_row)
{
	auto *tag = ods::tag::SheetRow(tag_->ns(), nullptr);
	auto *row = new ods::Row(this, tag, at_row);
	int vec_index = 0;
	foreach (auto *row, rows_)
	{
		if (row->UpToRow() > at_row)
			break;
		vec_index++;
	}
	rows_.insert(vec_index, row);
	tag_->subnodes().insert(vec_index, new ods::Node(tag));
	return row;
}

void
Sheet::PreSave()
{
	// if (column_ == nullptr)
	//{
		//mtl_warn("Fix");
	//	return;
	//}
	
	InitEnd();
	
	//auto &subnodes = tag_->subnodes();
	//subnodes.prepend(new ods::Node(column_->tag()));
}

ods::Row*
Sheet::row(qint32 column)
{ 
	qint32 current = 0;
	
	foreach (auto *row, rows_)
	{
		current += row->num_rows_repeated();
		
		if (current > column)
			return row;
		
	}
	return nullptr;
}

void
Sheet::SetColumnWidth(const int col_index, const QString &width)
{
	ods::Ns &ns = tag_->ns();
	auto *col_tag = ods::tag::SheetColumn(ns, nullptr);
	auto *column = new ods::Column(this, col_tag);
	column->SetNumColsRepeated(-1);
	
	// TODO: here check that last_column_width_set = column - 1;
	
	if (col_index - 1 != last_column_width_set_)
		AddColumnSpanUpTo(col_index);
	
	last_column_width_set_ = col_index;
	auto *style = book()->CreateColumnStyle();
	
	auto *tag = style->GetTag(ods::style::tag::SheetColumnProps);
	tag->AttrSet(ns.fo(), ods::style::kBreakBefore, ods::ns::kAuto);
	tag->AttrSet(ns.style(), ods::style::kColumnWidth, width);
	column->SetStyle(style);
	
	style = content_->book()->CreateStyle(ods::StyleFamilyId::Cell);
//	style->SetFontName("Arial");
	col_tag->AttrSet(ns.sheet(), ods::style::kDefaultCellStyleName,
		style->name());
	
	auto &subnodes = tag_->subnodes();
	subnodes.append(new ods::Node(col_tag));
}

void
Sheet::SetStyle(ods::Style *style)
{
	style_ = style;
	tag_->AttrSet(tag_->ns().sheet(), ods::style::kStyleName, style_->name());
}

} // namespace ods



















