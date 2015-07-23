#ifndef MY_GL_WIDGET
#define MY_GL_WIDGET

#include "Client.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include <QtOpenGL\qglWidget>
#include "Mat4x4.h"
#include "Camera.h"
#include <chrono>
#include <ctime>

class Army;
class MainWidget;

class MyGLWidget : public QGLWidget
{
	
protected:

	Client * c;
	
	Vaisseau * ship;
	ProjectileGL * projectile;

	std::vector<std::shared_ptr<PlayerGL>> backup;
	std::vector<std::shared_ptr<Projectile>> backupProj;

	std::shared_ptr<PlayerGL> player;

	QPoint lastPos;
	MainWidget * mw;


	Mat4x4 projection;
	Mat4x4 modelView;

	bool entered;

	float anglex;
	float angley;

	float m_z;
	Point2 m_relativeMouse;
	Point2 m_oldMousePos;

	Army* A;
	Army* B;

	float timeDelay;
	float timeElapsed;
	float totalTimeDelay;

	Camera cam;

	bool rightClick;
	Point2* selected;

	void initializeGL();
	void paintGL();
	void initGlDataToDraw();
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void resizeEvent(QResizeEvent *e);
	bool event(QEvent *e);
	

public:

	void setArmy(Army * tA, Army * tB){ A = tA; B = tB; }
	void eventWrapper(QEvent * e){ event(e); }
	void gameloop();
	void setMainWidget(MainWidget* m);

};

#endif