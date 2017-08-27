/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_ATTR_HPP_
#define ODS_ATTR_HPP_

#include "global.hxx"
#include "Prefix.hpp"
#include "err.hpp"

QT_FORWARD_DECLARE_CLASS(QXmlStreamAttributes)
QT_FORWARD_DECLARE_CLASS(QXmlStreamWriter)

namespace ods	{ // ods::
class Attrs;
class Prefix;

class ODS_API Attr
{
public:
	//==> used by ods::Tag
	Attr(ods::Prefix &prefix, const char *name);
	//<== used by ods::Tag
	virtual ~Attr();
	
	ods::Attr*
	Clone();
	
	bool
	Equals(ods::Prefix &prefix, const char *name) {
		return (prefix_.uri().id == prefix.uri().id) &&
			(strcmp(name_, name) == 0);
	}
	
	void
	Load(QXmlStreamAttributes &attrs);
	
	const char*
	name() const { return name_; }
	
	ods::Prefix&
	prefix() { return prefix_; }
	
	QString
	QualifiedName() const { return prefix_.With(name_); }
	
	bool
	ToDouble(double &d);
	
	bool
	ToInt32(qint32 &n);
	
	bool
	ToUint16(quint16 &n);
	
	const QString&
	value() const { return value_; }
	
	void
	value_set(const QString &s) { value_ = s; }
	
	void
	Write(QXmlStreamWriter &xml);

private:
	NO_ASSIGN_COPY_MOVE(Attr);
	
	const char		*name_ = nullptr;
	ods::Prefix		&prefix_;
	QString			value_;
};

} // ods::

#endif
