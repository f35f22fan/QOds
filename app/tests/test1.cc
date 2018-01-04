#include "test1.hh"

#include <QDir>
#include <ods/ods>

namespace qods {
namespace tests {

void
ReadCellsWithMultipleTextP()
{
	mtl_line("TEST");
	QString path = QDir::home().absoluteFilePath("multi_textp_cells.ods");
	ods::Book book(path);
	book.Print(0, 0, 0);
	book.Print(0, 1, 0);
}

void
ReadRandomCellValues()
{
	mtl_line("TEST");
	QString path = QDir::home().absoluteFilePath("random_cell_values.ods");
	ods::Book book(path);
	
	for (int r = 1; r < 5; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			if (!book.Print(0, r, c))
				break;
		}
	}
}

} // qods::tests::
} // qods::