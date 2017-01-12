/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "StyleFamily.hpp"
#include "../ns.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

StyleFamily::StyleFamily(const ods::StyleFamilyId f) :
	id_(f)
{}

StyleFamily::~StyleFamily()
{}

QString
StyleFamily::toString()
{
	if (IsCell())
		return QString(ods::ns::kSheetCell);
	else if (IsColumn())
		return QString(ods::ns::kSheetColumn);
	else if (IsRow())
		return QString(ods::ns::kSheetRow);
	else if (IsSheet())
		return QString(ods::ns::kSheet);
	return QStringLiteral("");
}

} // ods::style::
} // ods::
