/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Attr.hpp"
#include "Attrs.hpp"
#include <QXmlStreamWriter>

namespace ods	{ // ods::

Attr::Attr(ods::Prefix &prefix, const char *name) :
	name_(name),
	prefix_(prefix)
{}

Attr::~Attr()
{}

ods::Attr*
Attr::Clone()
{
	auto *attr = new ods::Attr(prefix_, name_);
	attr->value_set(value_);
	return attr;
}

void
Attr::Load(QXmlStreamAttributes &attrs)
{
	const QString &full_prefix = prefix_.With(name_);
	QStringRef ref = attrs.value(full_prefix);
	if (!ref.isEmpty())
		value_ = ref.toString();
}
/**
QString
Attr::QualifiedName() const {
	return prefix_.With(name_);
}
**/
bool
Attr::ToDouble(double &n)
{
	bool ok;
	auto tmp = value_.toDouble(&ok);
	if (ok)
		n = tmp;
	return ok;
}

bool
Attr::ToUint16(quint16 &n)
{
	bool ok;
	auto tmp = value_.toUShort(&ok);
	if (ok)
		n = tmp;
	return ok;
}

bool
Attr::ToInt32(qint32 &n)
{
	bool ok;
	auto tmp = value_.toInt(&ok);
	if (ok)
		n = tmp;
	return ok;
}

void
Attr::Write(QXmlStreamWriter &xml)
{
	if (!value_.isEmpty())
		xml.writeAttribute(QualifiedName(), value_);
}

} // ods::
