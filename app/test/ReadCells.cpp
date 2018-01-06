#include "ReadCells.hpp"

#include "util.hh"

#include <QDir>
#include <ods/ods>
#include <ods/CompareNumbers.hh>

static const auto file0 = QStringLiteral("random_cell_values.ods");
static const auto file1 = QStringLiteral("multi_textp_cells.ods");

QTEST_MAIN(ReadCells);

void
ReadCells::initTestCase()
{}

void
ReadCells::RandomValues()
{
	QString path = qods::test::util::test_files_dir_path() + file0;
	ods::Book book(path);
	
	auto *v = book.value(1, 0);
	QVERIFY(v != nullptr && v->IsString());
	
	v = book.value(3, 1);
	QVERIFY(v != nullptr && v->IsDouble());
	
	v = book.value(4, 3);
	QVERIFY(v != nullptr && v->IsDuration());
	
	auto *cell = book.cell(3, 3);
	QVERIFY((cell != nullptr) && cell->HasFormula());
	
	auto &val = cell->formula()->value();
	
	if (!val.IsDouble())
		QVERIFY(false);
	
	double num = *val.AsDouble();
	QVERIFY(ods::ApproximatelyEqual(num, 3.15, 0.0001));
}

void
ReadCells::WithMultipleTextP()
{
	QString path = qods::test::util::test_files_dir_path() + file1;
	ods::Book book(path);
	
	auto *v = book.value(0, 0);
	
	if (v == nullptr || !v->IsString())
		QVERIFY(false);
	
	auto *s = v->AsString();
	auto ba = s->toLocal8Bit();
	QVERIFY(s->count('\n') == 2);
	
	v = book.value(2, 1);
	
	if (v == nullptr || !v->IsString())
		QVERIFY(false);
	
	s = v->AsString();
	ba = s->toLocal8Bit();
	QVERIFY(s->count('\n') == 1);
}
