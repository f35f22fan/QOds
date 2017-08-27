/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_NS_HPP_
#define ODS_NS_HPP_

#include "Attr.hpp"
#include "err.hpp"
#include "global.hxx"
#include "ns.hxx"
#include "ods.hxx"
#include "Prefix.hpp"
#include "Tag.hpp"
#include <QMap>
#include <QXmlStreamReader>

namespace ods	{ // ods::

class ODS_API Ns
{
public:
	Ns(const ods::UriId);
	Ns(QXmlStreamReader*, const ods::UriId);
	virtual ~Ns();
	
	inline bool
	At(const char *kName) const
	{
		if (kName == nullptr)
			return true;
		return xml_->name() == QLatin1String(kName);
	}
	
	inline bool
	At(const ods::Prefix &prefix) const
	{
		QStringRef current = xml_->prefix();
		return (!current.isNull()) && (prefix.str() == current);
	}
	
	bool
	At(const ods::Prefix &prefix, const char *name) const;
	
	inline bool
	At(ods::Attr *attr) const { return At(attr->prefix(), attr->name()); }
	
	inline bool
	At(ods::Tag *tag) const { return At(tag->attr()); }
	
	ods::Prefix&
	config() { return prefix_config_; }
	
	ods::Prefix&
	dc() { return prefix_dc_; }
	
	ods::Prefix&
	draw() { return prefix_draw_; }
	
	ods::Prefix&
	fo() { return prefix_fo_; }
	
	ods::Prefix*
	GetPrefixByUriId(const ods::UriId);
	
	ods::Prefix&
	manifest() { return prefix_manifest_; }
	
	ods::Prefix&
	meta() { return prefix_meta_; }
	
	ods::Prefix&
	number() { return prefix_number_; }
	
	ods::Prefix&
	office() { return prefix_office_; }
	
	ods::Prefix&
	sheet() { return prefix_sheet_; }
	
	ods::Prefix&
	style() { return prefix_style_; }
	
	ods::Prefix&
	svg() { return prefix_svg_; }
	
	ods::Prefix&
	text() { return prefix_text_; }
	
	const QString&
	version() const { return version_; }
	
	void
	WriteNamespaces(QXmlStreamWriter &xml);
	
	QXmlStreamReader&
	xml() { return *xml_; }
	
	ods::Prefix&
	xlink() { return prefix_xlink_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Ns);
	
	void
	InitDefault();
	
	void
	Read();
	
	const ods::UriId	kVersionUriId_;
	ods::Prefix			prefix_config_;
	ods::Prefix			prefix_dc_;
	ods::Prefix			prefix_draw_;
	ods::Prefix			prefix_fo_;
	ods::Prefix			prefix_manifest_;
	ods::Prefix			prefix_meta_;
	ods::Prefix			prefix_number_;
	ods::Prefix			prefix_of_;
	ods::Prefix			prefix_office_;
	ods::Prefix			prefix_sheet_;
	ods::Prefix			prefix_style_;
	ods::Prefix			prefix_svg_;
	ods::Prefix			prefix_text_;
	ods::Prefix			prefix_xlink_;
	QString				version_;
	QXmlStreamReader	*xml_ = nullptr;
};

} // ods::

#endif
