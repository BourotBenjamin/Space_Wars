#define GLEW_STATIC 1
#include <GL\glew.h>
#include "MyGLWidget.h"
#include <QtGui\qevent.h>
#include "MainWidget.h"



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
	timeDelay = 1.0f / 60;
	c = new Client();

	ship = new Vaisseau("courbeVertex.vs", "courbeFragment.fs");
	ship->load();

	projectile = new ProjectileGL("courbeVertex.vs", "courbeFragment.fs");
	projectile->load();
	anglex = 0.f;
	angley = 0.f;
	rightClick = false;
	modelView.identity();
	//modelView.translate(0, 0, -7.0f);
	m_z = 0;
	m_relativeMouse = Point2();
	cam.lookAt(modelView);
	//mw->start();
}

void MyGLWidget::initGlDataToDraw()
{
	c->cv_m.lock();
	backup.clear();
	backupProj.clear();
	for (auto it = c->getPlayers().begin(); it != c->getPlayers().end(); ++it)
	{
		backup.push_back((*it));
		if ((*it)->getId() == c->getSelfID())
			player = (*it);
	}
	for (auto it = c->getProj().begin(); it != c->getProj().end(); ++it)
	{
		backupProj.push_back((*it));
	}
	c->cv_m.unlock();
}

void MyGLWidget::paintGL()
{
	initGlDataToDraw();
	glViewport(0, 0, width(), height());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam.lookAt(modelView);
	Mat4x4 world;
	
	for (auto it = backup.begin(); it != backup.end(); ++it)
	{
		std::shared_ptr<PlayerGL> p = (*it);
		glm::vec3 ppos = p->getPos();
		world.identity();
		//world.rotateY(-90.f);
		world.translate(ppos.x, ppos.y, ppos.z);
		
		//world.rotateX(p->getAngleX());
		//world.rotateY(p->getAngleY());
		ship->draw(projection, modelView, world, Point2(1.f, 0.f, 0.f), cam.getPos(), cam.getOrientation());
	}
	
	glm::vec3 posplGL = player->getPos();
	cam.setPosition(Point2(posplGL.x, posplGL.y, posplGL.z));
	glm::vec3 orplGL = player->getOrientation();

	
	for (auto it = backupProj.begin(); it != backupProj.end(); ++it)
	{
		glm::vec3 ppos = (*it)->position;
		world.identity();
		world.translate(ppos.x, ppos.y, ppos.z);
		
		//world.rotateX(p->getAngleX());
		//world.rotateY(p->getAngleY());
		
		projectile->draw(projection, modelView, world, Point2(1.f, 0.f, 0.f), cam.getPos(), cam.getOrientation());
	}

	/*for (int i = 0; i < c->getProjectileSize(); i++)
	{
		PlayerGL * p = c->getPlayerAt(i);
		glm::vec3 ppos = p->getPos();
		world.identity();
		world.translate(ppos.x, ppos.y, ppos.z);
		world.rotateX(p->getAngleX());
		world.rotateX(p->getAngleY());
		lol->draw(projection, modelView, world, Point2(1.f, 0.f, 0.f), cam.getPos(), cam.getOrientation());
	}*/
	/*world.identity();
	//world.rotateX(60);
	world.translate(1, 0, 4);
	
	//world.rotateY(30);
	ship->draw(projection, modelView, world, Point2(1.f, 0.f, 0.f), cam.getPos(), cam.getOrientation());

	world.identity();
	world.translate(-1, 0, 10);
	ship->draw(projection, modelView, world, Point2(0.f, 1.f, 0.f), cam.getPos(), cam.getOrientation());

	world.identity();
	world.translate(0, 2, 0);
	ship->draw(projection, modelView, world, Point2(0.f, 0.f, 1.f), cam.getPos(), cam.getOrientation()); 
	*/
}

void MyGLWidget::mousePressEvent(QMouseEvent * e)
{
	c->fire();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * e)
{
	if (!entered)
	{
		m_oldMousePos = Point2(e->x(), e->y(), m_z);
		entered = true;
	}
	if (e->x() <= 0 || e->x() >= width()-1 || e->y() <= 0 || e->y() >= height()-1)
	{
		std::cout << "lol";
		entered = false;
	}
		
	m_relativeMouse = Point2(e->x() - width() / 2, -e->y() + height() / 2, m_z) - (cam.getPos());
	
	cam.orienter(e->x() - m_oldMousePos.Getx(), e->y() - m_oldMousePos.Gety());
	m_oldMousePos = Point2(e->x(), e->y(), m_z);

	c->rotate((e->x() - m_oldMousePos.Getx())/0.05, (e->y() - m_oldMousePos.Gety())/0.05);

	/*QPoint glob = mapToGlobal(QPoint(width() / 2, height() / 2));
	QCursor::setPos(glob);
	lastPos = QPoint(width() / 2, height() / 2);
	QGLWidget::mouseMoveEvent(e);*/
	repaint();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent * e)
{
	
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
			//cam.orienter(-3, 0);
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
			return true;
		}
	}

	return QWidget::event(e);
}

void MyGLWidget::gameloop()
{
	timeElapsed = 0;

	float currentTime = std::clock() / 1000.f;
	static float totalTimeDelay = timeDelay + std::clock() / 1000.f;
	if (currentTime > totalTimeDelay)
	{
		totalTimeDelay = timeDelay + std::clock() / 1000.f;
		c->gameLoopStep(timeDelay);
		repaint();
	}
}

void MyGLWidget::setMainWidget(MainWidget* m){ mw = m; }
