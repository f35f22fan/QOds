/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_STYLE_HPP_
#define ODS_STYLE_HPP_

#include "decl.hxx"
#include "err.hpp"
#include "global.hxx"
#include "ods.hxx"
#include "style/decl.hxx"
#include "tag.hxx"
#include <QColor>

namespace ods	{ // ods::

class ODS_API Style
{
public:
	Style(ods::Book*, ods::Tag*, ods::style::StyleFamily*,
		const ods::StylePlace);
	virtual ~Style();
	
	ods::Style*
	Derive(const ods::StylePlace place = ods::StylePlace::NotSet);
	
	const QString&
	font_name() const { return font_name_; }
	
	double
	font_size() const { return font_size_; }
	
	void
	font_size_set(const double d) { font_size_ = d; }
	
	double
	FontSizeInInches();
	
	ods::FontSizeType
	font_size_type() const { return font_size_type_; }
	
	void
	font_size_type_set(const ods::FontSizeType t) { font_size_type_ = t; }

	ods::style::Currency*
	GetCurrencyStyle();

	ods::style::Date*
	GetDateStyle();
	
	ods::style::Percent*
	GetPercentStyle();
	
	ods::Tag*
	GetTag(ods::tag::func f);

	ods::style::Duration*
	GetDurationStyle();
	
	const QString&
	name() { return name_; }
	
	ods::Style*
	parent_style() const { return parent_style_; }
	
	void
	SetBackgroundColor(const QColor&);
	
	void
	SetBold(const bool flag = true);
	
	void
	SetBorder(ods::style::Border*);

	void
	SetCurrencyStyle(ods::style::Currency*);

	void
	SetDateStyle(ods::style::Date*);
	
	void
	SetFontName(const QString &font_name);
	
	void
	SetFontSize(const float size,
		const ods::FontSizeType size_type = ods::FontSizeType::Pt);
	
	void
	SetFontStyle(const ods::FontStyle);
	
	void
	SetFontWeight(const ods::FontWeight);
	
	void
	SetHAlignment(const ods::HAlign a);
	
	void
	SetItalic(const bool flag = true);
	
	void
	SetOptimalRowHeight(const double, const ods::FontSizeType);
	
	void
	SetParentStyle(ods::Style*);
	
	void
	SetPercentStyle(ods::style::Percent*);
	
	void
	SetTextColor(const QColor &color);

	void
	SetDurationStyle(ods::style::Duration*);
	
	void
	SetVAlignment(const ods::VAlign a);
	
	ods::style::StyleFamily*
	style_family() const { return style_family_; }
	
	ods::Tag*
	tag() const { return tag_; }

    void SetWrapOption(bool wrap);
private:
	NO_ASSIGN_COPY_MOVE(Style);
	
	void
	Init();
	
	void
	SetUniqueName();
	
	ods::Book				*book_ = nullptr;
	QString					font_name_;
	double					font_size_ = -1.0;
	ods::FontSizeType		font_size_type_ = ods::FontSizeType::NotSet;
	QString					name_;
	ods::Style				*parent_style_ = nullptr;

	ods::StylePlace			place_;
	ods::style::StyleFamily	*style_family_ = nullptr;
	ods::Tag				*tag_ = nullptr;

	ods::style::Substyle	*substyle_ = nullptr;
};

} // ods::

#endif
