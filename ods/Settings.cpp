/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Settings.hpp"
#include "Book.hpp"
#include "filename.hxx"
#include "Ns.hpp"
#include "Tag.hpp"
#include "tag.hh"
#include <QSaveFile>

namespace ods	{ // ods::

Settings::Settings(ods::Book *book) :
	book_(book)
{
	Init();
}

Settings::~Settings()
{}

void
Settings::Init()
{
	QString full_path = QDir(book_->temp_dir_path())
		.filePath(ods::filename::kSettings);
	QFile file(full_path);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		err_ = file.errorString();
		return;
	}
	QXmlStreamReader xml(&file);
	while(!xml.atEnd() && !xml.hasError())
	{
		if (xml.readNext() != QXmlStreamReader::StartElement)
			continue;
		if (xml.name() == ods::ns::kDocSettings) {
			ns_ = new ods::Ns(&xml, ods::UriId::Office);
			root_ = ods::tag::OfficeDocSettings(*ns_, nullptr);
			root_->Read();
		}
	}
}

void
Settings::Save(const QString &save_dir, QString &err)
{
	if (root_ == nullptr) {
		err = QStringLiteral("[Settings::Save] root_ = nullptr");
		return;
	}
	
	QSaveFile out(save_dir + QStringLiteral("/") + ods::filename::kSettings);
	out.open(QIODevice::WriteOnly);
	
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	root_->Write(xml, err);
	
	if (!err.isEmpty()) {
		out.cancelWriting();
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[Settings] QSaveFile:commit() failed");
	}
}

} // ods::
