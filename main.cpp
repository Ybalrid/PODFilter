#include "PODFilter.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PODFilter w;
	w.show();

	return a.exec();
}
