#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QtWidgets\qwidget.h>
#include "MyGLWidget.h"

class MainWidget :
	public QWidget
{
public:
	MainWidget();
	~MainWidget();

	void start();

private:

	MyGLWidget* newGL;
};

#endif // !MAIN_WIDGET_H