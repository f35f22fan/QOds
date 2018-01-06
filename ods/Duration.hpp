/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#pragma once

#include <QtGlobal>
#include <QtCore/QString>

#include "global.hxx"

namespace ods { // ods::

class ODS_API Duration
{
public:
	Duration();
	Duration(const qint32 hours, const qint32 minutes, const qint32 seconds);
	virtual ~Duration();
	
	Duration(const ods::Duration &rhs);
	
	bool
	operator==(const ods::Duration &rhs) const;
	
	operator QString();
	
	void
	Decode(const QString &str);
	
	qint32
	years() const { return years_; }
	
	void
	years_set(const qint32 n) { years_ = n; }
	
	qint32
	months() const { return months_; }
	
	void
	months_set(const qint32 n) { months_ = n; }
	
	qint32
	days() const { return days_; }
	
	void
	days_set(const qint32 n) { days_ = n; }
	
	qint32
	hours() const { return hours_; }
	
	void
	hours_set(const qint32 n) { hours_ = n; }
	
	qint32
	minutes() const { return minutes_; }
	
	void
	minutes_set(const qint32 n) { minutes_ = n; }
	
	qint32
	seconds() const { return seconds_; }
	
	void
	seconds_set(const qint32 n) { seconds_ = n; }

	QString
	ToString() const;
	
	bool
	valid() const { return valid_; }
	
	void
	valid_set(const bool b) { valid_ = b; }
	
private:
	
	qint32		years_ = 0;
	qint32		months_ = 0;
	qint32		days_ = 0;
	qint32		hours_ = 0;
	qint32		minutes_ = 0;
	qint32		seconds_ = 0;
	bool		valid_ = false;
};

} // ods::

