/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_REGION_HXX_
#define ODS_REGION_HXX_

#include "cell.hxx"
#include "ods.hxx"

namespace ods		{ // ods::
namespace region	{ // ods::region::

struct Token
{
	double num;
	ods::Op op = ods::Op::None;
};


} // ods::region::
} // ods::

#endif

