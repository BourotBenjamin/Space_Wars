#define GLEW_STATIC 1
#include <GL\glew.h>
#include "MyGLWidget.h"
#include <QtGui\qevent.h>



void MyGLWidget::initializeGL()
{
	glewInit();
	resize(800, 800);
	setMinimumSize(800, 800);
	selected = nullptr;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	setMouseTracking(true);
	projection.Perspective(45.f, 800, 800, 0.1f, 1000.f);
	cam = Camera(Point2(0, 0, -7.0f), Point2(0, 0, 0), Point2(0, 1, 0));
	lol = new Cube("courbeVertex.vs", "courbeFragment.fs");
	lol->load();
	anglex = 0.f;
	angley = 0.f;
	rightClick = false;
	modelView.identity();
	//modelView.translate(0, 0, -7.0f);
	m_z = 0;
	m_relativeMouse = Point2();
	cam.lookAt(modelView);

	listcube.push_back(std::shared_ptr<Cube>(new Cube("courbeVertex.vs", "courbeFragment.fs")));
	listcube.back()->load();
}

void MyGLWidget::paintGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam.lookAt(modelView);
	
	Mat4x4 world;
	world.identity();
	world.translate(1, 0, 4);
	lol->draw(projection, modelView, world, Point2(1.f,0.f,0.f), cam.getPos(), cam.getOrientation());

	world.identity();
	world.translate(-1, 0, 10);
	lol->draw(projection, modelView, world, Point2(0.f, 1.f, 0.f), cam.getPos(), cam.getOrientation());

	world.identity();
	world.translate(0, 2, 0);
	lol->draw(projection, modelView, world, Point2(0.f, 0.f, 1.f), cam.getPos(), cam.getOrientation());
	

	/*Mat4x4 world;
	for (auto it = A->getUnitsList().begin(); it != A->getUnitsList().end(); ++it)
	{
		Point p = (*it)->getPosition();
		
		world.identity();
		world.translate(p.getX(), 0, p.getY());
		lol->draw(projection, modelView, world, cam.getPos(), cam.getOrientation());
	}
	for (auto it = B->getUnitsList().begin(); it != B->getUnitsList().end(); ++it)
	{
		Point p = (*it)->getPosition();

		world.identity();
		world.translate(p.getX(), 0, p.getY());
		lol->draw(projection, modelView, world, cam.getPos(), cam.getOrientation());
	}*/
	
	//lol->load();

	
	/*for (auto it = listcube.begin(); it != listcube.end(); ++it)
		(*it)->draw(projection, modelView, world);
		*/
}

void MyGLWidget::mousePressEvent(QMouseEvent * e)
{
	
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * e)
{
	m_relativeMouse = Point2();
	m_relativeMouse = Point2(e->x() - width() / 2, -e->y() + height() / 2, m_z) - (cam.getPos());
	
	cam.orienter(e->x() - m_oldMousePos.Getx(), e->y() - m_oldMousePos.Gety());
	m_oldMousePos = Point2(e->x(), e->y(), m_z);

	repaint();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent * e)
{
	
	repaint();
}

void MyGLWidget::resizeEvent(QResizeEvent *e)
{

	
	projection.Perspective(45.0f, width(),height(), 0.1f,1000.0f );
}

bool MyGLWidget::event(QEvent *e)
{
	if (e->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(e);
		if (ke->key() == Qt::Key_Left) {
			cam.deplacer(2, 0, 0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Right) {
			cam.deplacer(3, 0, 0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Up) {
			cam.deplacer(0, 0, 0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Down) {
			cam.deplacer(1, 0, 0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Space) {
			cam.setPosition(Point2(0, 0, -7.f));
			modelView.identity();
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Plus) {
			m_z += 0.2;
			return true;
		}
		if (ke->key() == Qt::Key_Minus) {
			m_z -= 0.2;
			return true;
		}
	}

	return QWidget::event(e);
}

/*bool MyGLWidget::event(QEvent *e)
{
	if (e->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(e);
		if (ke->key() == Qt::Key_Left) {
			anglex += 5.73;
			cam.deplacer(2, 5.73f,0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Right) {
			//cam.setPosition(Point(cam.getPos().Getx() + 0.1, cam.getPos().Gety(), cam.getPos().Getz()));
			anglex -= 5.73;
			cam.deplacer(3, -5.73f, 0);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Up) {
			//cam.setPosition(Point(cam.getPos().Getx(), cam.getPos().Gety() - 0.1, cam.getPos().Getz()));
			angley -= 5.73;
			cam.deplacer(0, 0, -5.73f);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Down) {
			//cam.setPosition(Point(cam.getPos().Getx(), cam.getPos().Gety() + 0.1, cam.getPos().Getz()));
			angley += 5.73;
			cam.deplacer(1, 0, 5.73f);
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Space) {
			cam.setPosition(Point2(0, 0, -7.f));
			modelView.identity();
			cam.lookAt(modelView);
			repaint();
			return true;
		}
		if (ke->key() == Qt::Key_Plus) {
			m_z += 0.2;
			return true;
		}
		if (ke->key() == Qt::Key_Minus) {
			m_z -= 0.2;
			return true;
		}
	}

	return QWidget::event(e);
}*/
