#include "WriteOut.hpp"

#include <ods/ods>
#include <ods/CompareNumbers.hh>

#include "util.hh"

QTEST_MAIN(WriteOut);

void
WriteOut::initTestCase()
{}

void
WriteOut::Misc()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("Sheet1");
	auto *row = sheet->CreateRow(0);
	const QString str_val = QLatin1String("Hello, world!");
	const double d_val = 15.2;
	const double prc_val = 0.92;
	const double curr_val = 800.0;
	const auto dt_val = QDateTime(QDate(1833, 10, 28));
	const auto dur_val = ods::Duration(25, 59, 2); // 25h, 59m, 2s
	
	row->CreateCell(0)->SetValue(str_val);
	row->CreateCell(1)->SetValue(d_val);
	row->CreateCell(2)->SetPercentageValue(prc_val, 2);
	row->CreateCell(3)->SetCurrencyValue(curr_val);
	row->CreateCell(4)->SetValue(dt_val);
	row->CreateCell(5)->SetValue(dur_val);
	
	QString path;
	QVERIFY(qods::test::util::Save(book, "file.ods", &path));
	
	// now test what was written to the .ods file
	
	ods::Book b(path);
	auto *v = b.value(0, 0);
	QVERIFY(v != nullptr && v->IsString());
	QVERIFY(v->AsString() == str_val);
	
	v = b.value(0, 1);
	QVERIFY(v != nullptr && v->IsDouble());
	double d = *v->AsDouble();
	QVERIFY(ods::ApproximatelyEqual(d, d_val, 0.0001));
	
	v = b.value(0, 2);
	QVERIFY(v != nullptr && v->IsPercentage());
	double prc = *v->AsPercentage();
	QVERIFY(ods::ApproximatelyEqual(prc, prc_val, 0.0001));
	
	v = b.value(0, 3);
	QVERIFY(v != nullptr && v->IsCurrency());
	double curr = *v->AsCurrency();
	QVERIFY(ods::ApproximatelyEqual(curr, curr_val, 0.0001));
	
	//TBD check if should rename Date -> DateTime
	v = b.value(0, 4);
	QVERIFY(v != nullptr && v->IsDate());
	QDateTime dt = *v->AsDate();
	QVERIFY(dt == dt_val);
	
	v = b.value(0, 5);
	QVERIFY(v != nullptr && v->IsDuration());
	ods::Duration dur = *v->AsDuration();
	QVERIFY(dur == dur_val);
}
