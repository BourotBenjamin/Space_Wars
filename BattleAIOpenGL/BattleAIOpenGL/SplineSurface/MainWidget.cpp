#include "MainWidget.h"

#include <QtWidgets\qboxlayout.h>
#include <QtWidgets\qslider.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qpushbutton.h>

#include <QtGui\qevent.h>

#include "Army.hpp"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "training.hpp"
#include "fstream"
#include "Field.hpp"

Field Field::m_instance = Field();


MainWidget::MainWidget()
{

	
	QHBoxLayout * hLayout;
	this->setLayout(hLayout = new QHBoxLayout);
	QVBoxLayout * vLayout;
	hLayout->addLayout(vLayout = new QVBoxLayout);
	newGL = new MyGLWidget;
	hLayout->addWidget(newGL);

	/*QVBoxLayout* courbes;
	vLayout->addLayout(courbes = new QVBoxLayout);
	QVBoxLayout* typeCourbes;
	courbes->addLayout(typeCourbes = new QVBoxLayout);
	QHBoxLayout * hL1;
	typeCourbes->addLayout(hL1 = new QHBoxLayout);

	QPushButton * Bezier;
	QPushButton * Spline;
	hL1->addWidget(Bezier = new QPushButton("Bezier"));
	hL1->addWidget(Spline = new QPushButton("Spline"));
	QHBoxLayout * hL2;
	typeCourbes->addLayout(hL2 = new QHBoxLayout);

	QPushButton * SSpline;
	QPushButton * SBezier;
	QPushButton * SSESpline;
	hL2->addWidget(SSESpline = new QPushButton("Surface Simple Extrude"));
	hL2->addWidget(SSpline = new QPushButton("Surface Revolution"));
	hL2->addWidget(SBezier = new QPushButton("Surface Bezier"));

	QVBoxLayout* listCourbes;
	courbes->addLayout(listCourbes = new QVBoxLayout);
	listCourbes->addWidget(new QLabel("lol"));
	listCourbes->addWidget(new QLabel("lol"));
	listCourbes->addWidget(new QLabel("lol"));

	QHBoxLayout * hL3;
	courbes->addLayout(hL3 = new QHBoxLayout);
	QPushButton * leftb;
	QPushButton * rightb;
	hL3->addWidget(leftb = new QPushButton("Left"));
	hL3->addWidget(rightb = new QPushButton("Right"));
	QPushButton * upb;
	QPushButton * downb;
	hL3->addWidget(upb = new QPushButton("Up"));
	hL3->addWidget(downb = new QPushButton("Down"));

	QPushButton * clearScene;
	courbes->addWidget(clearScene = new QPushButton("Clear Scene"));

	connect(Bezier, SIGNAL(clicked()),
		newGL, SLOT(createBezier()));

	connect(Spline, SIGNAL(clicked()),
		newGL, SLOT(createSpline()));

	connect(SBezier, SIGNAL(clicked()),
		newGL, SLOT(createsBezier()));

	connect(SSESpline, SIGNAL(clicked()),
		newGL, SLOT(createSSESpline()));

	connect(SSpline, SIGNAL(clicked()),
		newGL, SLOT(createSSpline()));

	connect(leftb, SIGNAL(clicked()),
		newGL, SLOT(goLeft()));

	connect(rightb, SIGNAL(clicked()),
		newGL, SLOT(goRight()));

	connect(upb, SIGNAL(clicked()),
		newGL, SLOT(goUp()));

	connect(downb, SIGNAL(clicked()),
		newGL, SLOT(goDown()));

	connect(clearScene, SIGNAL(clicked()),
		newGL, SLOT(clearSceneGL()));
	*/
	resize(1200, 800);
	newGL->repaint();
}


MainWidget::~MainWidget()
{
}

void MainWidget::start()
{
	std::srand(time(NULL));
	int width, height;
	std::vector<std::unique_ptr<Army> > champions;
	try {
		std::ifstream in("Army_10_100.save");
		Army army = Army::load(in);
		std::cout << army << std::endl;
		champions.push_back(std::unique_ptr<Army>(new Army(army)));
	}
	catch (...) {

	}
	std::cout << "bound : width :" << std::endl;
	std::cin >> width;
	std::cout << "bound : height :" << std::endl;
	std::cin >> height;
	Field& F = Field::getInstance();
	F.setW(width);
	F.setH(height);
	std::shared_ptr<Army> army = train(10, 100, 5, 5, 100, champions, newGL);
	std::cout << *army << std::endl;
	std::ofstream out("Army_10_100.save");
	army->save(out);
	out.flush();
	out.close();
}
