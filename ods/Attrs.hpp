/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_ATTRS_HPP_
#define ODS_ATTRS_HPP_

#include "global.hxx"
#include "err.hpp"
#include <QXmlStreamAttributes>

class QXmlStreamReader;
class QXmlStreamWriter;

namespace ods	{ // ods::
class Attr;
class Prefix;

class ODS_API Attrs
{
public:
	Attrs();
	virtual ~Attrs();
	
	void
	Add(ods::Attr *attr) { attrs_.append(attr); }
	
	void
	Add(ods::Prefix &prefix, const char *name);

	QVector<ods::Attr*>&
	attrs() { return attrs_; }
	
	ods::Attrs*
	Clone();

	void
	Delete(ods::Prefix &prefix, const char *name);
	
	ods::Attr*
	Get(ods::Prefix &prefix, const char *name);
	
	void
	Load(QXmlStreamReader &xml);
	
	void
	Write(QXmlStreamWriter &xml);
	
private:
	NO_ASSIGN_COPY_MOVE(Attrs);
	
	QVector<ods::Attr*>		attrs_;
};

} // ods::

#endif
