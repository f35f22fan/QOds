#ifndef ODS_TIMEINFO_HPP_
#define ODS_TIMEINFO_HPP_

#include "err.hpp"
#include "global.hxx"

namespace ods	{ // ods::

namespace timeinfo { // ods::timeinfo::

enum class Order : quint8 {
	HOURS_MINUTES,
	HOURS_MINUTES_SECONDS
};

enum class Separator : quint8 {
	COLON
};

} // ods::timeinfo::

class ODS_API TimeInfo
{
public:
	TimeInfo();
	virtual ~TimeInfo();

	void
	CopyFrom(const TimeInfo&);

	const QString&
	data_style_name() const { return data_style_name_; }

	void
	data_style_name_set(const QString &s) { data_style_name_ = s; }

	bool
	Equals(const ods::TimeInfo &t) const;

	const QString&
	hours_number_style() const { return hours_number_style_; }

	const QString&
	minutes_number_style() const { return minutes_number_style_; }

	const QString&
	name() const { return name_; }

	ods::timeinfo::Order
	order() const { return order_; }

	void
	order_set(const ods::timeinfo::Order &r) { order_ = r; }

	const QString&
	seconds_number_style() const { return seconds_number_style_; }

	ods::timeinfo::Separator
	separator() const { return separator_; }

	void
	separator_set(const ods::timeinfo::Separator &r) { separator_ = r; }

	QString
	SeparatorAsString() const;

private:
	NO_ASSIGN_COPY_MOVE(TimeInfo);

	QString		data_style_name_;
	QString		hours_number_style_ = "long";
	QString		minutes_number_style_ = "long";
	QString		seconds_number_style_ = "long";
	QString		name_;
	ods::timeinfo::Order	order_ = ods::timeinfo::Order::HOURS_MINUTES;
	ods::timeinfo::Separator separator_ = ods::timeinfo::Separator::COLON;

};

} // ods::

#endif
