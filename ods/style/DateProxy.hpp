#ifndef ODS_STYLE_DATE_PROXY_HPP_
#define ODS_STYLE_DATE_PROXY_HPP_

#include "../err.hpp"
#include "../global.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API DateProxy
{
public:
	DateProxy();
	virtual ~DateProxy();

	const QString&
	name() const { return name_; }

	const QString&
	data_style_name() const { return data_style_name_; }

	void
	data_style_name_set(const QString &s) { data_style_name_ = s; }

private:
	NO_ASSIGN_COPY_MOVE(DateProxy);

	QString		data_style_name_;
	QString		name_;
};

} // ods::style::
} // ods::

#endif
