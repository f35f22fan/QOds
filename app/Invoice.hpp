/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */

#ifndef APP_INVOICE_HPP_
#define APP_INVOICE_HPP_

#include <ods/ods>

namespace app	{ // app::

class Item;

class Invoice
{
public:
	Invoice();
	virtual ~Invoice();
	
private:
	
	int // last row or -1 on error
	CreateBillToHeader(const int kLastRow);
	
	int
	CreateNotes(const int kLastRow);
	
	int // last row or -1 on error
	CreateSellerHeader();
	
	int
	CreateTable(QVector<app::Item*>*, const int kLastRow);
	
	int
	CreateTableHeader(const int kLastRow);
	
	QVector<app::Item*>*
	GenItems();
	
	void
	Init();
	
	ods::Book book_;
	ods::Sheet *sheet_ = nullptr;
};

} // app::


#endif
