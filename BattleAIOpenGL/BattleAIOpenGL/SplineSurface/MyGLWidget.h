#ifndef MY_GL_WIDGET
#define MY_GL_WIDGET

#include "Cube.h"
#include <QtOpenGL\qglWidget>
#include "Mat4x4.h"
#include "Camera.h"
#include "Cube.h"

class Army;

class MyGLWidget : public QGLWidget
{
	
protected:

	std::vector<std::shared_ptr<Cube>> listcube;
	Cube * lol;

	Mat4x4 projection;
	Mat4x4 modelView;

	float anglex;
	float angley;

	float m_z;
	Point2 m_relativeMouse;
	Point2 m_oldMousePos;

	Army* A;
	Army* B;

	Camera cam;

	bool rightClick;
	Point2* selected;

	void initializeGL();
	void paintGL();
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void resizeEvent(QResizeEvent *e);
	bool event(QEvent *e);
	

public:

	void setArmy(Army * tA, Army * tB){ A = tA; B = tB; }
	void eventWrapper(QEvent * e){ event(e); }


};

#endif