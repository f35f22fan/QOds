/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_SETTINGS_HPP_
#define ODS_SETTINGS_HPP_

#include "err.hpp"
#include "global.hxx"

namespace ods	{ // ods::

class Book;
class Ns;
class Tag;

class ODS_API Settings
{
public:
	Settings(ods::Book*);
	virtual ~Settings();
	
	void
	Save(const QString &save_dir, QString &err);

private:
	NO_ASSIGN_COPY_MOVE(Settings);
	
	void
	Init();
	
	ods::Book		*book_ = nullptr;
	QString			err_;
	ods::Tag		*root_ = nullptr;
	ods::Ns			*ns_ = nullptr;
};

} // ods::

#endif
