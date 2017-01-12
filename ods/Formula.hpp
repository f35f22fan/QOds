/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_FORMULA_HPP_
#define ODS_FORMULA_HPP_

#include "cell.hxx"
#include "decl.hxx"
#include "err.hpp"
#include "global.hxx"
#include "Value.hpp"
#include <QByteArray>
#include <QString>
#include <QStringRef>
#include <QVector>

namespace ods	{ // ods::

class ODS_API Formula
{
public:
	Formula();
	Formula(ods::Cell *cell, const QString &ref);
	virtual ~Formula();
	
	void
	Add(ods::Cell*, ods::Sheet *sheet = nullptr);
	
	void
	Add(const double d) { formula_ += QString::number(d); }
	
	void
	Add(const ods::Grouping g);
	
	void
	Add(const ods::Op op);
	
	ods::Formula*
	Clone();
	
	const QString&
	error() { return error_; }
	
	void
	error_set(const QString &s) { error_ = s; }
	
	const QString&
	formula() const { return formula_; }
	
	void
	formula_set(const QString &s) { formula_ = s; }
	
	bool
	GetDouble(ods::CellRef *cell_ref, double &num);
	
	bool
	HasAnError() const { return error_.size() > 0; }
	
	ods::Cell*
	source() { return source_; }
	
	void
	source_set(ods::Cell *cell) { source_ = cell; }
	
	void
	UpdateValue();
	
	ods::Value&
	value() { return value_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Formula);
	
	void
	Init(const QStringRef&);
	
	QString			error_;
	ods::Cell		*source_ = nullptr;
	QString			formula_;
	ods::Value		value_;
};

} // ods::
#endif
