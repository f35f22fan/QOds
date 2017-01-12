/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_TAG_HH_
#define ODS_TAG_HH_

#include "global.hxx"

namespace ods	{ // ods::
class Ns;
class Tag;
namespace tag	{ // ods::tag::

namespace bits	{ // ods::tag::bits::

const quint8
	HasTextP	= 1,
	Used		= 2,
	XmlNs		= 4;
} // ods::tag::bits::

ODS_API ods::Tag*	BackgroundImage(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CalculationSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItem(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapEntry(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapIndexed(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapNamed(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemSet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CoveredSheetCell(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CurrencySymbol(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DcCreator(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DcDate(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DrawFrame(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DrawImage(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Manifest(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ManifestFileEntry(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Number(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberPercentageStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberText(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeBody(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeDocContent(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeDocSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeSpreadsheet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Sheet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetCell(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetColumn(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetRow(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SvgDesc(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SvgTitle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextDate(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextP(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextPageCount(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextPageNumber(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextSheetName(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextSpan(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextTime(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextTitle(ods::Ns&, ods::Tag*);

} // ods::tag::
} // ods::
#endif

