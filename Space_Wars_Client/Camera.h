#ifndef DEF_CAMERA
#define DEF_CAMERA


#include "Point2.h"
#include "Mat4x4.h"

// Classe

class Camera
{ 
private:

    float m_phi;
    float m_theta;
	Point2 m_orientation;

	Point2 m_axeVertical;
	Point2 m_deplacementLateral;

	Point2 m_position;
	Point2 m_pointCible;

public:

    Camera();
    Camera(Point2 position, Point2 pointCible, Point2 axeVertical);
    ~Camera();

    void orienter(float xRel, float yRel);
    void deplacer(int i, float xrel, float yrel);
    void lookAt(Mat4x4 &modelview);
	Point2 getPos();
	Point2 getOrientation(){ return m_orientation; }
	Point2 getstraff(){ return m_deplacementLateral; }
	Point2 getAxeV(){ return m_axeVertical; }
	void setPointcible(Point2 pointCible);
	void setPosition(Point2 position);


};

#endif
