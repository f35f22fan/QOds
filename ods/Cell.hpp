/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#pragma once

#include "global.hxx"

#include "err.hpp"
#include <QByteArray>
#include <QFile>

#include "cell.hxx"
#include "decl.hxx"
#include "i18n.hxx"
#include "tag.hh"
#include "tag.hxx"
#include "Value.hpp"

namespace ods	{ // ods::

class ODS_API Cell
{
public:
	Cell(ods::Row*, ods::Tag*, const qint32 col_start);
	virtual ~Cell();
	
	QString
	Address() const;
	
	ods::Cell*
	cell_next() const { return cell_next_; }
	
	void
	cell_next_set(ods::Cell *cell) { cell_next_ = cell; }
	
	ods::Cell*
	cell_prev() const { return cell_prev_; }
	
	void
	cell_prev_set(ods::Cell *cell) { cell_prev_ = cell; }
	
	ods::Cell*
	Clone();
	
	quint16
	col_count() const { return num_cols_spanned_ * num_cols_repeated_; }
	
	qint32
	col_start() const { return col_start_; }
	
	void
	col_start_set(const int n) { col_start_ = n; }
	
	int
	ComputeHeightInPixels(const int col_width_in_pixels);
	
	ods::DrawFrame*
	CreateDrawFrame(const QFile &file);
	
	QString
	Diagnose() { return value_.Diagnose(); }
	
	ods::Formula*
	formula() const { return formula_; }
	
	void
	formula_set(ods::Formula *f) { formula_ = f; }
	
	ods::Tag*
	GetDrawFrameTag();
	
	QString*
	GetTextP();
	
	bool
	HasFormula() const { return formula_ != nullptr; }
	
	bool
	HasTextP() const;
	
	void
	InitEnd();
	
	bool
	is_covered() const;
	
	bool
	IsEmpty() const { return value_.IsNotSet() && !HasTextP(); }
	
	bool
	IsEmpty2() const { return IsEmpty() && style_ == nullptr; }
	
	quint16
	num_cols_repeated() const { return num_cols_repeated_; }
	
	void
	num_cols_repeated_set(const quint16 n) { num_cols_repeated_ = n; }
	
	quint16
	num_cols_spanned() const { return num_cols_spanned_; }
	
	void
	num_cols_spanned_set(const quint16 n) { num_cols_spanned_ = n; }
	
	quint16
	num_rows_spanned() const { return num_rows_spanned_; }
	
	void
	num_rows_spanned_set(const quint16 n) { num_rows_spanned_ = n; }
	
	ods::Row*
	row() const { return row_; }
	
	void
	Set(ods::Prefix &prefix, const char *key, const QString &value);
	
	void
	SetCovered(const bool covered = true);

	void
	SetCurrencyValue(const double num, ods::Style *style = nullptr);
	
	void
	SetFormula(ods::Formula*, ods::Style *style = nullptr);
	
	void
	SetNumColsRepeated(const quint16 num);
	
	void
	SetPercentageType(const qint8 decimal_places = 0);
	
	void
	SetPercentageValue(const double d, const qint8 decimal_places = 0);
	
	void //@@@HasDoc
	SetRowColSpan(const quint16, const quint16);
	
	void
	SetStyle(ods::Style*);
	
	void
	SetValue(const QDateTime&, ods::Style *style = nullptr);

	void
	SetValue(const ods::Duration&, ods::Style *style = nullptr);

	void
	SetValue(const double);
	
	void
	SetValue(const QString&);
	
	ods::Style*
	style() const { return style_; }
	
	ods::Tag*
	tag() { return tag_; }
	
	qint32
	UpToColumn() const { return col_start_ + col_count() - 1; }
	
	ods::Value&
	value() { return value_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Cell);
	
	ods::Tag*
	GetTag(ods::Prefix &p, const char *name, ods::tag::func);
	
	void
	Init();

	void
	UpdateDrawFrame();
	
	qint32			col_start_ = -1;
	quint16			num_cols_repeated_ = 1;
	quint16			num_cols_spanned_ = 1;
	//quint16		num_matrix_rows_spanned_;
	quint16			num_rows_spanned_ = 1;
	
	ods::Cell		*cell_next_ = nullptr;
	ods::Cell		*cell_prev_ = nullptr;
	
	ods::DrawFrame	*draw_frame_ = nullptr;
	ods::Formula	*formula_ = nullptr;
	ods::Row		*row_ = nullptr;
	ods::Style		*style_ = nullptr;
	ods::Tag		*tag_ = nullptr;
	ods::Value		value_;
};

} // ods::
