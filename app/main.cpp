/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
 */

#include "examples1.hpp"
#include "examples2.hpp"

#include <ods/ods>
#include <QGuiApplication>

int
main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	
	mtl_line("QOds version: %u.%u.%u\n",ods::version_major(),
		ods::version_minor(), ods::version_micro());
	
	// Lesson01_CreateBookAndSetColumnWidths();
	// Lesson02_CreateCellsOfDifferentTypes();
	// Lesson06_CellSpan();
	// Lesson08_ReadFormula();
	// Lesson10_WriteCrossSheetFormula();
	// Lesson14_ReadDate();
	// Lesson15_WriteDate();
	// Lesson16_ReadDuration();
	// Lesson17_WriteDuration();
	Lesson19_CreateSampleInvoice();
	// Lesson20_TestWrapAdjustment();
	
	return 0;
}

