/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */


#ifndef ODS_STYLE_BORDER_HPP_
#define ODS_STYLE_BORDER_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"
#include <QColor>

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API Border
{
public:
	Border();
	virtual ~Border();
	
	ods::style::Border*
	Derive();
	
	void
	SetColor(const QColor c) { color_ = c.name(QColor::HexRgb); }
	
	quint8
	sides() const { return sides_; }
	
	void
	sides_set(const quint8 bits) { sides_ = bits; }
	
	void
	SetStyle(const ods::BorderStyle s);
	
	void
	SetWidth(const ods::BorderWidth);
	
	void
	SetWidth(const QString &w) { width_ = w; }
	
	QString
	toString();
	
protected:
	void
	CopyTo(ods::style::Border*);
	
	void
	SetColor(const QString &c) { color_ = c; }
	
	void
	SetStyle(const QString &style) { border_style_ = style; }

private:
	NO_ASSIGN_COPY_MOVE(Border);
	
	quint8			sides_ = ods::BorderSideAll;
	QString			border_style_;
	QString			color_;
	bool			is_none_ = false;
	QString			width_;
};

} // ods::style::
} // ods::

#endif
