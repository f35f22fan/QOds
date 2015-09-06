#include "TimeInfo.hpp"

namespace ods	{ // ods::

TimeInfo::TimeInfo()
{}

TimeInfo::~TimeInfo()
{}

void
TimeInfo::CopyFrom(const TimeInfo &r)
{
	data_style_name_ = r.data_style_name();
	order_ = r.order();
	separator_ = r.separator();
}

bool
TimeInfo::Equals(const ods::TimeInfo &r) const
{
	if (data_style_name_ != r.data_style_name())
		return false;
	if (hours_number_style_ != r.hours_number_style())
		return false;
	if (minutes_number_style_ != r.minutes_number_style())
		return false;
	if (seconds_number_style_ != r.seconds_number_style())
		return false;
	if (separator_ != r.separator())
		return false;
	return true;
}

QString
TimeInfo::SeparatorAsString() const
{
	if (separator_ == ods::timeinfo::Separator::COLON)
		return QLatin1String(":");
	return QLatin1String(":"); // add more options if ever needed
}

} // ods::
