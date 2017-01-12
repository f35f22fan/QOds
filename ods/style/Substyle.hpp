/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_STYLE_SUBSTYLE_HPP_
#define ODS_STYLE_SUBSTYLE_HPP_

#include "../err.hpp"
#include "decl.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

enum class Id : quint32 {
	NotSet = 0,
	Currency = 1,
	Date = 2,
	Duration = 4,
	Percent = 8
};

class Substyle
{
public:
	Substyle();
	virtual ~Substyle();

	ods::style::Currency*
	AsCurrency() { return (ods::style::Currency*) data_; }

	ods::style::Date*
	AsDate() { return (ods::style::Date*) data_; }

	ods::style::Duration*
	AsDuration() { return (ods::style::Duration*) data_; }

	ods::style::Percent*
	AsPercent() { return (ods::style::Percent*) data_; }

	void
	currency_set(ods::style::Currency *p) {
		id_ = ods::style::Id::Currency;
		data_ = p;
	}

	void
	date_set(ods::style::Date *p) {
		id_ = ods::style::Id::Date;
		data_ = p;
	}

	void
	duration_set(ods::style::Duration *p) {
		id_ = ods::style::Id::Duration;
		data_ = p;
	}

	void
	percent_set(ods::style::Percent *p) {
		id_ = ods::style::Id::Percent;
		data_ = p;
	}

	bool
	IsCurrency() const { return id_ == ods::style::Id::Currency; }

	bool
	IsDate() const { return id_ == ods::style::Id::Date; }

	bool
	IsDuration() const { return id_ == ods::style::Id::Duration; }

	bool
	IsNotSet() const { return id_ == ods::style::Id::NotSet; }

	bool
	IsPercent() const { return id_ == ods::style::Id::Percent; }

private:
	NO_ASSIGN_COPY_MOVE(Substyle);

	ods::style::Id id_ = ods::style::Id::NotSet;
	void *data_ = nullptr;
};

} // ods::style::
} // ods::

#endif
