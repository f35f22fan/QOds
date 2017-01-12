/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */

#include "examples1.hpp"
#include "examples2.hpp"

#include <ods/ods>
#include <QtCore>

int
main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	qDebug().nospace() << "QOds version: " << ods::version_major() << "."
		<< ods::version_minor() << "." << ods::version_micro();
	
	//Lesson08_ReadFormula();
	//Lesson10_WriteCrossSheetFormula();
	Lesson19_CreateSampleInvoice();
	//Lesson14_ReadDate();
	//Lesson15_WriteDate();
	//Lesson16_ReadDuration();
	//Lesson17_WriteDuration();
	
	return 0;
}

