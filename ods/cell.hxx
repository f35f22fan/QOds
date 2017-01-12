/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_CELL_HXX_
#define ODS_CELL_HXX_

#include <QDate>
#include <QtGlobal>
#include <QString>
#include <QTime>

#include "ods.hxx"

namespace ods	{ // ods::
namespace cell	{ // ods::cell::

enum class Type : quint8
{
	Normal,
	Placeholder,
	Covered
};

} // ods::cell::
} // ods::


#endif
