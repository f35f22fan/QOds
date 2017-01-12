/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Manifest.hpp"
#include "Book.hpp"
#include "DrawFrame.hpp"
#include "filename.hxx"
#include "Node.hpp"
#include "Ns.hpp"
#include "Tag.hpp"
#include "tag.hh"
#include <QSaveFile>

static const auto kMetaInf = "META-INF";

namespace ods	{ // ods::

Manifest::Manifest(ods::Book *book) :
	book_(book)
{
	if (book_->extracted())
		Read();
	else
		InitDefault();
}

Manifest::~Manifest()
{
	delete ns_;
	delete root_;
}

void
Manifest::Add(const QString &path, const QString &media_type)
{
	auto *tag = ods::tag::ManifestFileEntry(*ns_, nullptr);
	root_->SubtagAdd(tag);
	tag->AttrSet(ns_->manifest(), ods::ns::kFullPath, path);
	tag->AttrSet(ns_->manifest(), ods::ns::kMediaType, media_type);
}

void
Manifest::Add(ods::DrawFrame *df)
{
	Add(df->GetRelativeUri(), df->mime_type());
}

bool
Manifest::HasSettings()
{
	if (root_ == nullptr)
		return false;
	
	foreach (auto *node, root_->subnodes()) {
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		const auto *str = tag->GetAttrString(ns_->manifest(),
			ods::ns::kFullPath);
		if (str == nullptr)
			continue;
		if (*str == ods::filename::kSettings)
			return true;
	}
	return false;
}

void
Manifest::InitDefault()
{
	ns_ = new ods::Ns(ods::UriId::Manifest);
	root_ = ods::tag::Manifest(*ns_, nullptr);
	
	Add("/", "application/vnd.oasis.opendocument.spreadsheet");
	Add(ods::filename::kContent, ods::ns::kTextXml);
	Add(ods::filename::kMeta, ods::ns::kTextXml);
	Add(ods::filename::kStyles, ods::ns::kTextXml);
}

void
Manifest::Read()
{
	QString meta_path = QDir(book_->temp_dir_path()).filePath(kMetaInf);
	QFile file(QDir(meta_path).filePath(ods::filename::kManifest));
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
		if (xml.name() == ods::ns::kManifest) {
			ns_ = new ods::Ns(&xml, ods::UriId::Manifest);
			root_ = ods::tag::Manifest(*ns_, nullptr);
			root_->Read();
		}
	}
}

void
Manifest::Save(const QString &save_dir, QString &err)
{
	if (root_ == nullptr)
	{
		err = QStringLiteral("[Manifest::Save] root_ = nullptr");
		return;
	}
	const QString kDirPath = save_dir + QStringLiteral("/") + kMetaInf;
	QDir dir(kDirPath);
	if (!dir.exists())
	{
		if (!dir.mkpath(".")) {
			err_ = QStringLiteral("[Manifest] mkdir failed");
			return;
		}
	}
	const auto kFilePath = kDirPath + QStringLiteral("/")
		+ ods::filename::kManifest;
	QSaveFile out(kFilePath);
	out.open(QIODevice::WriteOnly);
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	//auto bits = root_->bits() & ~ods::Tag::kXmlNs;
	//root_->bits_set(bits);
	root_->Write(xml, err);
	
	if (!err.isEmpty())
	{
		out.cancelWriting();
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[Manifest] QSaveFile:commit() failed");
	}
}

} // ods::
