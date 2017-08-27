/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_PREFIX_HPP_
#define ODS_PREFIX_HPP_

#include "err.hpp"
#include "global.hxx"
#include "ods.hxx"
#include<QXmlStreamWriter>

namespace ods	{ // ods::

class ODS_API Prefix
{
public:
	Prefix(const ods::Uri &uri);
	virtual ~Prefix();
	
	const QString&
	str() const { return str_; }
	
	void
	str_set(const QString &s) { str_ = s; }
	
	const ods::Uri&
	uri() const { return uri_; }
	
	const QString&
	With(const char *name);
	
	inline void
	Write(QXmlStreamWriter &xml) const
	{
		if (!str_.isEmpty())
			xml.writeNamespace(QLatin1String(uri_.str), str_);
	}
	
private:
	NO_ASSIGN_COPY_MOVE(Prefix);
	
	QMap<const char*, QString>	map_;
	QString						str_;
	const ods::Uri				&uri_;
	
};

} // ods::

#endif
