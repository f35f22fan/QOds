/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_REGION_HPP_
#define ODS_REGION_HPP_

#include "err.hpp"
#include "global.hxx"
#include "region.hxx"
#include <QString>
#include <QVector>

namespace ods	{ // ods::

class Value;

class Region
{
protected:
	Region();
public:
	Region(const QString &s);
	virtual ~Region();
	
	int
	deep() const { return deep_; }
	
	void
	deep_set(const int n) { deep_ = n; }
	
	int
	end_index() const { return end_index_; }
	
	void
	end_index_set(const int n) { end_index_ = n; }
	
	const QString&
	error() { return error_; }
	
	void
	error_set(const QString &s) { error_ = s; }
	
	void
	Eval(ods::Value&);
	
	bool
	HasAnError() const { return error_.size() > 0; }
	
	void
	Print();
	
	bool // returns true on success
	ProcessAddAndSub();
	
	bool // returns true on success
	ProcessMultAndDiv();
	
	int
	start_index() const { return start_index_; }
	
	void
	start_index_set(const int n) { start_index_ = n; }
	
	const QString&
	str() const { return str_; }
	
	void
	str_set(const QString &s) { str_ = s; }
	
private:
	NO_ASSIGN_COPY_MOVE(Region);
	
	void
	Init(const QString &kFormula);
	
	void
	ParseString();
	
	ods::Region *current_region_ = nullptr;
	int	deep_ = 0;
	int	end_index_ = -1;
	int	start_index_ = -1;
	QString	str_, error_, formula_;
	QVector<ods::region::Token*> tokens_;
};

} // ods::
#endif
