/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Substyle.hpp"

#include "Currency.hpp"
#include "Date.hpp"
#include "Duration.hpp"
#include "Percent.hpp"

namespace ods	{ // ods::
namespace style	{ // ods::style::

Substyle::Substyle()
{}

Substyle::~Substyle()
{
	if (IsNotSet())
		return;
	if (IsCurrency())
		delete AsCurrency();
	else if (IsDate())
		delete AsDate();
	else if (IsDuration())
		delete AsDuration();
	else if (IsPercent()) {
		// don't delete manually
		// cause it's deleted automatically in ods::~Book()
	}
}

} // ods::style::
} // ods::
