/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_COLUMN_HPP_
#define ODS_COLUMN_HPP_

#include "global.hxx"
#include "err.hpp"

namespace ods	{ // ods::

class Ns;
class Sheet;
class Style;
class Tag;

class ODS_API Column
{
public:
	Column(ods::Sheet *sheet, ods::Tag*);
	virtual ~Column();
	
	qint32
	column_count() const { return column_count_; }
	
	void
	SetNumColsRepeated(const qint32 num);
	
	ods::Sheet*
	sheet() const { return sheet_; }
	
	void
	SetStyle(ods::Style*);
	
	ods::Tag*
	tag() const { return tag_; }

private:
	NO_ASSIGN_COPY_MOVE(Column);
	
	void
	Init();
	
	qint32		column_count_ = -1;
	ods::Sheet	*sheet_ = nullptr;
	ods::Style	*style_ = nullptr;
	ods::Tag	*tag_ = nullptr;
};

} // ods::

#endif
