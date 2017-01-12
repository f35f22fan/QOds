/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_META_HH_
#define ODS_META_HH_

#include "global.hxx"

namespace ods	{ // ods::
class Ns;
class Tag;
namespace meta	{ // ods::meta::

ODS_API ods::Tag*
CreationDate(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
DocumentStatistic(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
EditingCycles(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
EditingDuration(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
Generator(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
InitialCreator(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
Office(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
OfficeDocument(ods::Ns&, ods::Tag*);

} // ods::meta::
} // ods::
#endif
