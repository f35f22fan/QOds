/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_STYLE_STYLEFAMILY_HPP_
#define ODS_STYLE_STYLEFAMILY_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API StyleFamily
{
public:
	StyleFamily(const ods::StyleFamilyId);
	virtual ~StyleFamily();
	
	bool
	IsCell() const { return id_ == ods::StyleFamilyId::Cell; }
	
	bool
	IsColumn() const { return id_ == ods::StyleFamilyId::Column; }
	
	bool
	IsRow() const { return id_ == ods::StyleFamilyId::Row; }
	
	bool
	IsSheet() const { return id_ == ods::StyleFamilyId::Sheet; }
	
	ods::StyleFamilyId
	id() { return id_; }
	
	QString
	toString();

private:
	NO_ASSIGN_COPY_MOVE(StyleFamily);
	
	ods::StyleFamilyId		id_;
};

} // ods::style::
} // ods::

#endif
