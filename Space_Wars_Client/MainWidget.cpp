#include "MainWidget.h"

#include <QtWidgets\qboxlayout.h>
#include <QtWidgets\qslider.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qpushbutton.h>

#include <QtGui\qevent.h>



MainWidget::MainWidget()
{

	
	QHBoxLayout * hLayout;
	this->setLayout(hLayout = new QHBoxLayout);
	QVBoxLayout * vLayout;
	hLayout->addLayout(vLayout = new QVBoxLayout);
	newGL = new MyGLWidget;
	hLayout->addWidget(newGL);

	resize(1200, 800);
}


MainWidget::~MainWidget()
{
}

void MainWidget::start()
{

}

