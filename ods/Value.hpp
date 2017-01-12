/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_data_HPP_
#define ODS_data_HPP_

#include "cell.hxx"
#include "err.hpp"
#include "global.hxx"
#include "ods.hh"
#include "ods.hxx"

#include <QString>
#include <QXmlStreamAttributes>

namespace ods	{

class Attrs;
class Ns;
class Tag;

class ODS_API Value
{
public:
	Value();
	Value(void *v, const ods::Type kType);
	virtual ~Value();
	
	void
	AppendString(const QString &s);
	
	bool*
	AsBool() const { return (bool*) data_; }

	double*
	AsCurrency() const { return AsDouble(); }
	
	QDateTime*
	AsDate() const { return (QDateTime*) data_; }
	
	double*
	AsDouble() const { return (double*) data_; }

	ods::Duration*
	AsDuration() const { return (ods::Duration*) data_; }

	double*
	AsPercentage() const { return AsDouble(); }
	
	QString*
	AsString() const { return (QString*) data_; }
	
	void
	CopyTo(ods::Value&);
	
	void
	DeleteData();
	
	QString
	Diagnose();
	
	void*
	get() { return data_; }
	
	bool
	IsBool() const { return type_ == ods::Type::Bool; }
	
	bool
	IsCurrency() const { return type_ == ods::Type::Currency; }
	
	bool
	IsDate() const { return type_ == ods::Type::Date; }
	
	bool
	IsDouble() const { return type_ == ods::Type::Double; }

	bool
	IsDuration() const { return type_ == ods::Type::Duration; }

	bool
	IsNotSet() const { return type_ == ods::Type::NotSet; }

	bool
	IsPercentage() const { return type_ == ods::Type::Percentage; }
	
	bool
	IsString() const { return type_ == ods::Type::String; }
	
	void
	Read(ods::Ns &ns, ods::Attrs &attrs);
	
	void
	ReadTextP(ods::Tag *tag);
	
	void
	set(void *value) { DeleteData(); data_ = value; }
	
	void
	set(void *value, const ods::Type kType) {
		DeleteData();
		data_ = value;
		type_ = kType;
	}

	void
	SetCurrency(const double d);

	void
	SetDate(const QDateTime &r);
	
	void
	SetDouble(const double d);

	void
	SetDuration(const ods::Duration &r);

	void
	SetPercentage(const double d);
	
	void
	SetString(const QString &s);
	
	QString
	toString() const;
	
	ods::Type
	type() const { return type_; }
	
	const char*
	TypeToString() const { return ods::TypeToString(type_); }
	
	void
	type_set(const ods::Type kType) { type_ = kType; }
	
private:
	NO_ASSIGN_COPY_MOVE(Value);
	
	void *data_ = nullptr;
	ods::Type type_ = ods::Type::NotSet;
};

} // namespace ods
#endif
