#pragma once

#include <QTest>

class WriteOut : public QObject
{
	Q_OBJECT
	
private slots:
	
	void
	initTestCase();
	
	void
	Misc();
};