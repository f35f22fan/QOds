/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_SHEET_HPP_
#define ODS_SHEET_HPP_

#include "err.hpp"
#include "global.hxx"
#include "Tag.hpp"
#include <QString>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)
QT_FORWARD_DECLARE_CLASS(QXmlStreamWriter)

namespace ods	{

class Book;
class Column;
class Content;
class Ns;
class Row;
class Style;
class Tag;

class ODS_API Sheet
{
public:
	Sheet(ods::Content *content, ods::Tag*);
	virtual ~Sheet();
	
	void
	Add(ods::Row *row) { rows_.push_back(row); }
	
	ods::Book*
	book();
	
	qint32
	CalcRowCount();
	
	//ods::Column*
	//column() const { return column_; }
	
	ods::Content*
	content() const { return content_; }
	
	ods::Row*
	CreateRow(const qint32 at_row);
	
	const QByteArray&
	err() const { return err_; }
	
	ods::Row*
	GetPrevRow(const qint32 at_row);
	
	void
	InitEnd();
	
	ods::Row*
	InsertPlaceholder(const qint32 at_row, const qint32 row_repeat);
	
	ods::Row*
	InsertRow(const qint32 at_row);
	
	const QString&
	name() const { return name_; }
	
	ods::Ns&
	ns() const { return tag_->ns(); }
	
	void
	PreSave();
	
	ods::Row* // error => nullptr
	row(qint32 column);
	
	QVector<ods::Row*>*
	rows() { return &rows_; }
	
	void // e.g. width = "0.889in"
	SetColumnWidth(const int col_index, const QString &width);
	
	void
	SetStyle(ods::Style*);
	
	ods::Style*
	style() const { return style_; }
	
	ods::Tag*
	tag() const { return tag_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Sheet);
	
	void
	AddColumnSpanUpTo(const int col_index);
	
	void
	Init();
	
	void
	InitDefault();
	
	int last_column_width_set_ = -1; // must be -1 by default
	ods::Content		*content_ = nullptr;
	QByteArray			err_;
	QVector<ods::Row*>	rows_;
	QString				name_;
	ods::Style			*style_ = nullptr;
	ods::Tag			*tag_ = nullptr;
};

} // namespace ods
#endif
