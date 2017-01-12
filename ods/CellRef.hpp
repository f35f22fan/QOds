/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_CELLREF_HPP_
#define ODS_CELLREF_HPP_

#include "err.hpp"
#include "decl.hxx"

namespace ods	{ // ods::

class CellRef
{
public:
	CellRef();
	virtual ~CellRef();

	qint32
	col() const { return col_; }

	void
	col_set(const qint32 n) { col_ = n; }

	qint32
	row() const { return row_; }

	void
	row_set(const qint32 n) { row_ = n; }

	ods::Sheet*
	sheet() { return sheet_; }

	void
	sheet_set(ods::Sheet *s) { sheet_ = s; }

private:
	NO_ASSIGN_COPY_MOVE(CellRef);

	qint32 col_ = -1;
	qint32 row_ = -1;
	ods::Sheet *sheet_ = nullptr;
};

} // ods::

#endif
