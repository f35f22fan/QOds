/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */

#ifndef APP_UTIL_HPP_
#define APP_UTIL_HPP_

#include <ods/ods>

QString
GetCellValue(ods::Cell *cell);

void
Save(ods::Book &book);

#endif
