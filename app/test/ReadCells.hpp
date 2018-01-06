#pragma once

#include <QTest>

class ReadCells : public QObject
{
	Q_OBJECT
	
private slots:
	
	void
	initTestCase();
	
	void
	RandomValues();
	
	void
	WithMultipleTextP();
	
};
