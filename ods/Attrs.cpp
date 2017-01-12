/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Attrs.hpp"
#include "Attr.hpp"
#include "ns.hxx"
#include "Prefix.hpp"
#include <string.h>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace ods	{ // ods::

Attrs::Attrs()
{}

Attrs::~Attrs()
{
	foreach (auto *attr, attrs_)
		delete attr;
}

void
Attrs::Add(ods::Prefix &prefix, const char *name)
{
	attrs_.append(new ods::Attr(prefix, name));
}

ods::Attrs*
Attrs::Clone()
{
	auto *inst = new ods::Attrs();
	auto &vec = inst->attrs();
	foreach (auto *attr, attrs_)
		vec.append(attr->Clone());
	return inst;
}

void
Attrs::Delete(ods::Prefix &prefix, const char *name)
{
	for (int i = 0; i < attrs_.size(); i++)
	{
		auto *attr = attrs_[i];
		ods::Prefix &curr_prefix = attr->prefix();
		if (prefix.uri().id != curr_prefix.uri().id)
			continue;
		if (strcmp(name, attr->name()) != 0)
			continue;
		attrs_.remove(i);
		return;
	}
}

ods::Attr*
Attrs::Get(ods::Prefix &prefix, const char *name)
{
	foreach (auto *attr, attrs_)
	{
		ods::Prefix &curr_prefix = attr->prefix();
		if (prefix.uri().id != curr_prefix.uri().id)
			continue;
		if (strcmp(name, attr->name()) == 0)
			return attr;
	}
	//only reached if code is buggy
	return nullptr;
}

void
Attrs::Load(QXmlStreamReader &xml)
{
	auto attribs = xml.attributes();
	foreach (auto *attr, attrs_)
		attr->Load(attribs);
}

void
Attrs::Write(QXmlStreamWriter &xml)
{
	foreach (auto *attr, attrs_)
		attr->Write(xml);
}

} // ods::
