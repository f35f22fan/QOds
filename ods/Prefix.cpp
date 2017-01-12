/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Prefix.hpp"

namespace ods	{ // ods::

Prefix::Prefix(const ods::Uri &uri) :
	uri_(uri)
{}

Prefix::~Prefix()
{}

const QString&
Prefix::With(const char *name)
{
	const QString &value = map_[name];
	if (!value.isEmpty())
		return value;
	map_[name] = str_ + QStringLiteral(":") + name;
	return map_[name];
}

} // ods::
