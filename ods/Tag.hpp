/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_TAG_HPP_
#define ODS_TAG_HPP_

#include "Attr.hpp"
#include "Attrs.hpp"
#include "err.hpp"
#include "global.hxx"
#include "Node.hpp"
#include "Prefix.hpp"
#include "tag.hh"
#include "tag.hxx"
#include <QVector>

namespace ods	{ // ods::
class Base;
class Node;
class Ns;

class ODS_API Tag
{
public:
	Tag(ods::Ns&, ods::tag::func);
	virtual ~Tag();
	
	void
	Add(ods::Prefix &prefix, const char *name)
	{
		if (attrs_ == nullptr)
			attrs_ = new ods::Attrs();
		attrs_->Add(prefix, name);
	}
	
	ods::Attr*
	attr() { return attr_; }
	
	void
	attr_set(ods::Attr *attr)
	{
		if (attr_ != nullptr)
			delete attr_;
		attr_ = attr;
	}
	
	void
	attr_set(ods::Prefix &prefix, const char *name) {
		attr_ = new ods::Attr(prefix, name);
	}
	
	ods::Attrs*
	attrs() { return attrs_; }
	
	void
	attrs_set(ods::Attrs *attrs) { attrs_ = attrs; }
	
	void
	AttrDelete(ods::Prefix &prefix, const char *key);

	void
	AttrSet(ods::Prefix &prefix, const char *key, const QString &value);
	
	quint8
	bits() const { return bits_; }
	
	void
	bits_set(const quint8 n) { bits_ = n; }
	
	ods::Tag*
	Clone();
	
	void
	DeleteSubnodes();
	
	ods::tag::func
	func() { return func_; }
	
	void
	func_set(ods::tag::func f) { func_ = f; }
	
	const QString*
	GetAttrString(ods::Prefix &prefix, const char *name);
	
	ods::Tag*
	GetSubtag(ods::Prefix &prefix, const char *name);
	
	ods::Tag*
	GetSubtag(ods::tag::func f, const qint8 id_num = -1);
	
	QString*
	GetTextP();

	qint8
	id_num() const { return id_num_; }

	void
	id_num_set(const qint8 n) { id_num_ = n; }
	
	bool
	IsAnyCell() const { return
		ods::tag::SheetCell == func_ ||
		ods::tag::CoveredSheetCell == func_; }
	
	bool
	IsCell() const { return ods::tag::SheetCell == func_; }
	
	bool
	IsColumn() const { return ods::tag::SheetColumn == func_; }
	
	bool
	IsRow() const { return ods::tag::SheetRow == func_; }
	
	bool
	IsSheet() const { return ods::tag::Sheet == func_; }
	
	ods::Tag*
	New() { return func_(ns_, nullptr); }
	
	ods::Ns&
	ns() { return ns_; }
	
	QString
	QualifiedName() const { return attr_->QualifiedName(); }
	
	void
	Read();
	
	void
	SetPrintXmlns(const bool a) {
		if (a)
			bits_ |= ods::tag::bits::XmlNs;
		else
			bits_ &= ~ods::tag::bits::XmlNs;
	}
	
	void
	SetTextP(const QString &value);
	
	void
	SubfuncAdd(ods::tag::func);
	
	void
	SubnodeAdd(ods::Node *node) { subnodes_.append(node); }
	
	QVector<ods::Node*>&
	subnodes() { return subnodes_; }
	
	void
	SubtagAdd(ods::Tag *tag) { SubnodeAdd(new ods::Node(tag)); }
	
	bool
	used() const { return (bits_ & ods::tag::bits::Used) != 0; }
	
	void
	used_set(const bool a) {
		if (a)
			bits_ |= ods::tag::bits::Used;
		else
			bits_ &= ~ods::tag::bits::Used;
	}
	
	void
	Write(QXmlStreamWriter &xml, QString &err);
	
private:
	NO_ASSIGN_COPY_MOVE(Tag);
	
	ods::Attr				*attr_ = nullptr;
	ods::Attrs				*attrs_ = nullptr;
	ods::tag::func			func_;
	ods::Ns					&ns_;
	QVector<ods::tag::func>	subfuncs_;
	QVector<ods::Node*>		subnodes_;
	quint8					bits_ = 0;
	qint8					id_num_ = -1;
};

} // ods::

#endif
