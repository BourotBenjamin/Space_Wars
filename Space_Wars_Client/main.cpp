#include <QtWidgets/qapplication.h>
#include "MainWidget.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	MainWidget glWid;
	glWid.show();
	//glWid.start();
	return app.exec();
}