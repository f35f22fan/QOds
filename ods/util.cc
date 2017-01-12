/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "util.hh"
#include <QMimeDatabase>

namespace ods	{ // ods::
namespace util	{ // ods::util::

QString
GetMimeType(const QString &kFilePath)
{
	static QMimeDatabase db;
	auto mime = db.mimeTypeForFile(kFilePath);
	return mime.name();
}

} // ods::util::
} // ods::
