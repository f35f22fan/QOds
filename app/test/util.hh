#pragma once

#include <ods/err.hpp>
#include <ods/Book.hpp>

namespace qods {
namespace test {
namespace util {

QString
test_files_dir_path()
{
	QDir dir(QCoreApplication::applicationDirPath());
	
	if (!dir.cdUp() || !dir.cdUp())
		mtl_line();
	
	return dir.absolutePath() + "/app/test/data_files/";
}

bool
Save(ods::Book &book, const QString &file_name, QString *saved_to)
{
	auto path = QDir::temp().filePath(file_name);
	
	if (saved_to != nullptr)
		*saved_to = path;
	
	QFile target(path);
	QString err = book.Save(target);
	
	if (!err.isEmpty())
	{
		auto ba = err.toLocal8Bit();
		mtl_line("%s", ba.data());
	}
	
	return err.isEmpty();
}

}}} // qods::test::util::
