/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_STYLE_MANAGER_HPP_
#define ODS_STYLE_MANAGER_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"
#include <QString>
#include <QXmlStreamReader>

class QXmlStreamWriter;

namespace ods	{ // ods::

class Book;
class Ns;
class Style;
class Tag;

namespace style	{ // ods::style::

class ODS_API Manager
{
public:
	Manager(ods::Book *book);
	virtual ~Manager();
	
	void
	ApplyFontFace(const QString &kFontName, ods::Tag *tag);
	
	ods::Tag*
	automatic_styles_tag() const { return automatic_styles_tag_; }
	
	const QString&
	err() const { return err_; }
	
	void
	InitDefault();
	
	ods::Ns&
	ns() { return *ns_; }
	
	ods::Tag*
	styles_tag() const { return styles_tag_; }
	
	void
	Save(const QString &save_dir, QString &err);

private:
	NO_ASSIGN_COPY_MOVE(Manager);
	
	void
	InitDefaultStyles();
	
	void
	InitFontFaceDecls();
	
	void
	Read();
	
	ods::Tag			*root_tag_ = nullptr;
	ods::Tag			*automatic_styles_tag_ = nullptr;
	ods::Tag			*styles_tag_ = nullptr;
	ods::Tag			*font_face_decls_tag_ = nullptr;
	QVector<QString>	font_names_;
	ods::Tag			*master_styles_tag_ = nullptr;
	ods::Book			*book_ = nullptr;
	QString				err_;
	ods::Ns				*ns_ = nullptr;
};

} // ods::style::
} // ods::

#endif
