/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */


#include "Border.hpp"
#include "style.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

Border::Border()
{
	sides_ = ods::BorderSideAll;
	SetStyle(ods::BorderStyle::Solid);
	color_ = QStringLiteral("#000000");
	width_ = QStringLiteral("0.06pt");
}

Border::~Border()
{}

void
Border::CopyTo(ods::style::Border *b)
{
	b->SetColor(color_);
	b->sides_set(sides_);
	b->SetStyle(border_style_);
	b->SetWidth(width_);
}

ods::style::Border*
Border::Derive()
{
	auto *border = new ods::style::Border();
	CopyTo(border);
	return border;
}

void
Border::SetStyle(const ods::BorderStyle s)
{
	if (s == ods::BorderStyle::Solid)
		border_style_ = QStringLiteral("solid");
	else if (s == ods::BorderStyle::None)
		//border_style_ = QStringLiteral("none");
		is_none_ = true;
	
	else if (s == ods::BorderStyle::Dashed)
		border_style_ = QStringLiteral("dashed");
	else if (s == ods::BorderStyle::Dotted)
		border_style_ = QStringLiteral("dotted");
	else if (s == ods::BorderStyle::Double)
		border_style_ = QStringLiteral("double");
	else if (s == ods::BorderStyle::Inset)
		border_style_ = QStringLiteral("inset");
	else if (s == ods::BorderStyle::Outset)
		border_style_ = QStringLiteral("outset");
}

void
Border::SetWidth(const ods::BorderWidth w)
{
	if (w == ods::BorderWidth::Medium)
		width_ = "1.0pt";
	else if (w == ods::BorderWidth::Thick)
		width_ = "3.0pt";
	else // if (w == ods::BorderStyle::Thin)
		width_ = "0.5pt";
}

QString
Border::toString()
{
	if (is_none_)
		return QStringLiteral("none");
	return width_ + ods::kSpace + border_style_ + ods::kSpace + color_;
}

} // ods::style::
} // ods::
