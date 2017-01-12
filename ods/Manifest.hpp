/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_MANIFEST_HPP_
#define ODS_MANIFEST_HPP_

#include "err.hpp"
#include "global.hxx"

namespace ods	{ // ods::

class Book;
class DrawFrame;
class Ns;
class Tag;

class ODS_API Manifest
{
public:
	Manifest(ods::Book*);
	virtual ~Manifest();
	
	void
	Add(ods::DrawFrame*);
	
	bool
	HasSettings();
	
	void
	Save(const QString &save_dir, QString &err);

private:
	NO_ASSIGN_COPY_MOVE(Manifest);
	
	void
	Add(const QString &key, const QString &value);
	
	void
	InitDefault();
	
	void
	Read();
	
	ods::Book		*book_ = nullptr;
	QString			err_;
	ods::Tag		*root_ = nullptr;
	ods::Ns			*ns_ = nullptr;
};

} // ods::

#endif
