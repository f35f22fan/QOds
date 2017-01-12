/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Column.hpp"
#include "Ns.hpp"
#include "Style.hpp"
#include "style/style.hxx"
#include "Tag.hpp"

namespace ods	{ // ods::

Column::Column(ods::Sheet *sheet, ods::Tag *tag) :
	sheet_(sheet),
	tag_(tag)
{
	Init();
}

Column::~Column()
{}

void
Column::Init()
{
	auto *attrs = tag_->attrs();
	if (attrs == nullptr)
		return;
	auto &ns = tag_->ns();
	auto *attr = attrs->Get(ns.sheet(), ods::ns::kNumColsRepeated);
	if (attr != nullptr)
		attr->ToInt32(column_count_);
	//attr = attrs->Get(ns.sheet(), ods::style::kStyleName);
	//if (attr != nullptr)
}

void
Column::SetNumColsRepeated(const qint32 num)
{
	auto &ns = tag_->ns();
	column_count_ = num;
	if (column_count_ > 0)
		tag_->AttrSet(ns.sheet(), ods::ns::kNumColsRepeated,
			QString::number(num));
}

void
Column::SetStyle(ods::Style *style)
{
	style_ = style;
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.sheet(), ods::style::kStyleName, style->name());
}

} // ods::

















