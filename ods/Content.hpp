/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#pragma once

#include "global.hxx"
#include "ns.hxx"
#include "ods.hxx"
#include "err.hpp"
#include <QFile>
#include <QHash>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

namespace ods	{

class Book;
class Ns;
class Sheet;
class Style;
class Tag;

class ODS_API Content
{
public:
	Content(ods::Book *book);
	virtual ~Content();
	
	ods::Tag*
	automatic_styles_tag() const { return automatic_styles_tag_; }
	
	ods::Book*
	book() { return book_; }

	ods::Sheet*
	CreateSheet(const QString &sheet_name);
	
	const QString&
	err() const { return err_; }
	
	void
	InitDefault();
	
	void
	InitEnd();
	
	ods::Ns&
	ns() const { return *ns_; }

	void
	Read();
	
	void
	Save(const QString &save_dir, QString &err);
	
	void
	Scan(ods::Tag *parent);
	
	ods::Sheet*
	sheet(int index);
	
	ods::Sheet*
	sheet(const QString &name);
	
	QVector<ods::Sheet*>&
	sheets() { return sheets_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Content);
	
	void
	InitAutomaticStyles();

	void
	PreSave();
	
	ods::Tag				*automatic_styles_tag_ = nullptr;
	const QString			base_path_;
	ods::Book				*book_ = nullptr;
	ods::Tag				*doc_content_ = nullptr;
	ods::Tag				*font_face_decls_tag_ = nullptr;
	QString					err_;
	QFile					file_;
	ods::Ns					*ns_ = nullptr;
	ods::Tag				*office_body_ = nullptr;
	ods::Tag				*office_spreadsheet_ = nullptr;
	QVector<ods::Sheet*>	sheets_;
};

} // ods::
