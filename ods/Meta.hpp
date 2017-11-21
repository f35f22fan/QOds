/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_META_HPP_
#define ODS_META_HPP_

#include "err.hpp"
#include "global.hxx"
#include "Duration.hpp"
#include <QDateTime>
#include <QFile>
#include <QMap>

namespace ods	{

class Book;
class Ns;
class Tag;

class ODS_API Meta
{
public:
	Meta(ods::Book*);
	virtual ~Meta();
	
	const QString&
	err() const { return err_; }
	
	bool
	error() const { return err_.size() > 0; }
	
	void
	Save(const QString &save_dir, QString &err);
	
private:
	NO_ASSIGN_COPY_MOVE(Meta);
	
	void
	InitDefault();
	
	void
	Read();
	
	ods::Book		*book_ = nullptr;
	QString			err_;
	ods::Ns			*ns_ = nullptr;
	ods::Tag		*office_doc_ = nullptr;
	ods::Tag		*office_meta_ = nullptr;
	
	/**
	qint32				cell_count_ = -1;
	QDateTime			creation_date_;
	QDateTime			dc_date_;
	qint32				editing_cycles_ = - 1;
	ods::Duration		editing_duration_;
	QString				generator_;
	qint32				object_count_ = -1;
	qint32				sheet_count_ = -1;
	**/
};

} // namespace ods
#endif
