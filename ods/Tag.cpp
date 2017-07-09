/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Tag.hpp"
#include "Attr.hpp"
#include "Attrs.hpp"
#include "Node.hpp"
#include "Ns.hpp"

namespace ods	{ // ods::

Tag::Tag(ods::Ns &ns, ods::tag::func cf) :
	func_(cf),
	ns_(ns)
{}

Tag::~Tag()
{
	delete attr_;
	delete attrs_;
	DeleteSubnodes();
}

void
Tag::AttrDelete(ods::Prefix &prefix, const char *key)
{
	if (attrs_ != nullptr)
		attrs_->Delete(prefix, key);
}

void
Tag::AttrSet(ods::Prefix &prefix, const char *key, const QString &value)
{
	if (attrs_ == nullptr)
		attrs_ = new ods::Attrs();
	auto *attr = attrs_->Get(prefix, key);
	if (attr == nullptr) {
		attr = new ods::Attr(prefix, key);
		attrs_->Add(attr);
	}
	attr->value_set(value);
}

ods::Tag*
Tag::Clone()
{
	auto *tag = this->New();
	tag->attrs_set(attrs_->Clone());
	tag->attr_set(attr_->Clone());
	return tag;
}

void
Tag::DeleteSubnodes()
{
	foreach (auto *node, subnodes_)
		delete node;
	subnodes_.clear();
}

const QString*
Tag::GetAttrString(ods::Prefix &prefix, const char *name)
{
	auto *attr = attrs_->Get(prefix, name);
	if (attr == nullptr)
		return nullptr;
	return &attr->value();
}

ods::Tag*
Tag::GetSubtag(ods::Prefix &prefix, const char *name)
{
	foreach (auto *node, subnodes_) {
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		if (tag->attr()->Equals(prefix, name))
			return tag;
	}
	return nullptr;
}

ods::Tag*
Tag::GetSubtag(ods::tag::func f, const qint8 id_num)
{
	foreach (auto *node, subnodes_) {
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		if (tag->func() != f)
			continue;
		if (id_num >= 0 && tag->id_num() != id_num)
			continue;
		return tag;
	}
	return nullptr;
}

void
Tag::Read()
{
	if (attrs_ == nullptr)
		attrs_ = new ods::Attrs();
	func_(ns_, this);
	auto &xml = ns_.xml();
	attrs_->Load(xml);
	auto token = QXmlStreamReader::NoToken;
	ods::Tag *append_tag;
	QVector<ods::Tag*> subtags;
	
	foreach (auto *func, subfuncs_)
		subtags.append(func(ns_, nullptr));
	
	while (token != QXmlStreamReader::EndElement || !ns_.At(attr_))
	{
		token = xml.readNext();
		if (token == QXmlStreamReader::Characters)
		{
			const QString text = xml.text().toString();
			//qDebug() << "Tag::Read text:" << text;
			SubnodeAdd(new ods::Node(text));
			continue;
		}
		
		if (token != QXmlStreamReader::StartElement)
			continue;
		
		foreach (auto *tag, subtags)
		{
			if (!ns_.At(tag))
				continue;
			if (tag->used()) {
				append_tag = tag->New();
			} else {
				append_tag = tag;
				tag->used_set(true);
			}
			SubnodeAdd(new ods::Node(append_tag));
			append_tag->Read();
			break;
		}
	}
	
	foreach (auto *tag, subtags)
	{
		if (!tag->used())
			delete tag;
	}
}

void
Tag::SetTextP(const QString &value)
{
	ods::Tag *textp = GetSubtag(ns_.text(), ods::ns::kP);
	
	if (textp == nullptr)
	{
		textp = ods::tag::TextP(ns_, nullptr);
		subnodes_.append(new ods::Node(textp));
	} else {
		textp->DeleteSubnodes();
	}
	
	textp->subnodes().append(new ods::Node(value));
	bits_ |= ods::tag::bits::HasTextP;
}

QString*
Tag::GetTextP()
{
	ods::Tag *textp = GetSubtag(ns_.text(), ods::ns::kP);
	
	if (textp == nullptr)
		return nullptr;
	
	auto &vec = textp->subnodes();
	
	foreach (auto *node, vec)
	{
		if (node->IsString())
			return node->String();
	}
	
	return nullptr;
}

void
Tag::SubfuncAdd(ods::tag::func f)
{
	subfuncs_.append(f);
}

void
Tag::Write(QXmlStreamWriter &xml, QString &err)
{
	xml.writeStartElement(attr_->QualifiedName());
	
	if (bits_ & ods::tag::bits::XmlNs)
		ns_.WriteNamespaces(xml);
	if (attrs_ != nullptr)
		attrs_->Write(xml);
	foreach (auto *node, subnodes_)
	{
		if (node->IsTag())
		{
			node->Tag()->Write(xml, err);
			if (!err.isEmpty())
				return;
		} else {
			xml.writeCharacters(*node->String());
		}
	}
	xml.writeEndElement();
}

} // ods::
