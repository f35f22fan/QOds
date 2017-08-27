/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_HH_
#define ODS_HH_

#include <QStringRef>
#include <QDateTime>
#include <QGlobalStatic>
#include <QXmlStreamAttributes>

#include "cell.hxx"
#include "decl.hxx"
#include "global.hxx"
#include "Duration.hpp"

QT_FORWARD_DECLARE_CLASS(QXmlStreamWriter)

namespace ods	{ // ods::

class Ns;

ODS_API QChar
CharFromOp(const ods::Op);

ODS_API ods::Op // error => ods::Op::NONE
CharToOp(const QChar sign);

ODS_API ods::CellRef* // error => nullptr
CreateCellRef(const QStringRef &s, ods::Book *book);

ODS_API ods::Cell* // error => nullptr
FindCell(ods::CellRef *ref, ods::Cell *source);

ODS_API QString
FontSizeToString(const double size, const ods::FontSizeType tp);

ODS_API qint32
ColumnLettersToNumber(const QStringRef &letters);

ODS_API QString
ColumnNumberToLetters(const qint32 kColumn);

ODS_API ods::Type
TypeFromString(const QString &ods_type);

ODS_API const char* // nullptr if not found
TypeToString(const ods::Type &value_type);

ODS_API quint32
version_major();

ODS_API quint32
version_micro();

ODS_API quint32
version_minor();

} // ods::

#endif


