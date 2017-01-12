/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_FILENAME_HXX_
#define ODS_FILENAME_HXX_

#include <QString>

#ifndef ods_const
#define ods_const const char * const
#endif

namespace ods		{ // ods::
namespace filename	{ // ods::filename::

ods_const kContent		= "content.xml";
ods_const kMediaDirName	= "media";
ods_const kManifest		= "manifest.xml";
ods_const kMeta			= "meta.xml";
ods_const kMimeType		= "mimetype";
ods_const kSettings		= "settings.xml";
ods_const kStyles		= "styles.xml";

} // ods::filename::
} // ods::

#endif
