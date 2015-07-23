#include "Camera.h"

Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_pointCible()
{

}

Camera::Camera(Point2 position, Point2 pointCible, Point2 axeVertical) : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(axeVertical), m_deplacementLateral(), m_position(position), m_pointCible(pointCible)
{
    // Actualisation du point ciblé

    setPointcible(pointCible);
}

Camera::~Camera()
{

}

void Camera::orienter(float xRel, float yRel)
{
    // Récupération des angles

    m_phi += -yRel * 0.1;
	m_theta += -xRel * 0.1;


    // Limitation de l'angle phi

    if(m_phi > 89.0)
        m_phi = 89.0;

    else if(m_phi < -89.0)
        m_phi = -89.0;
		

    // Conversion des angles en radian

    float phiRadian = m_phi * M_PI / 180;
    float thetaRadian = m_theta * M_PI / 180;


    // Si l'axe vertical est l'axe X

    if(m_axeVertical.Getx() == 1.0)
    {
        // Calcul des coordonnées sphériques

		m_orientation.Setx(std::sin(phiRadian));
		m_orientation.Sety(std::cos(phiRadian) * std::cos(thetaRadian));
		m_orientation.Setz(std::cos(phiRadian) * std::sin(thetaRadian));
    }


    // Si c'est l'axe Y

    else if(m_axeVertical.Gety() == 1.0)
    {
        // Calcul des coordonnées sphériques

		m_orientation.Setx(std::cos(phiRadian) * std::sin(thetaRadian));
		m_orientation.Sety(std::sin(phiRadian));
		m_orientation.Setz(std::cos(phiRadian) * std::cos(thetaRadian));
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des coordonnées sphériques

		m_orientation.Setx(std::cos(phiRadian) * std::cos(thetaRadian));
		m_orientation.Sety(std::cos(phiRadian) * std::sin(thetaRadian));
		m_orientation.Setz(std::sin(phiRadian));
    }


    // Calcul de la normale

	m_deplacementLateral = Point2::crossProduct(m_axeVertical, m_orientation);
    m_deplacementLateral.normalize();


    // Calcul du point ciblé pour OpenGL

    m_pointCible = m_position + m_orientation;
}

void Camera::deplacer(int i, float xrel, float yrel)
{
    // Gestion de l'orientation

    orienter(xrel, yrel);


    // Avancée de la caméra

    if(i==0)
    {
		m_position = m_position + m_orientation * 0.5;//Point2::crossProduct(m_deplacementLateral, m_orientation); 
        m_pointCible = m_position + m_orientation;
    }


    // Recul de la caméra

    if(i==1)
    {
		m_position = m_position - m_orientation* 0.5;//Point2::crossProduct(m_deplacementLateral, m_orientation); //m_orientation;
        m_pointCible = m_position + m_orientation;
    }


    // Déplacement vers la gauche

    if(i==2)
    {
		m_position = m_position + m_deplacementLateral* 0.5;
        m_pointCible = m_position + m_orientation;
    }


    // Déplacement vers la droite

    if(i==3)
    {
		m_position = m_position - m_deplacementLateral * 0.5;
        m_pointCible = m_position + m_orientation;
    }
}

void Camera::lookAt(Mat4x4 &modelview)
{
    modelview.lookAt(m_position, m_pointCible, m_axeVertical);
}

Point2 Camera::getPos()
{
	return m_position;
}

void Camera::setPointcible(Point2 pointCible)
{
    // Calcul du vecteur orientation

    m_orientation = m_pointCible - m_position;
    m_orientation.normalize();


    // Si l'axe vertical est l'axe X

    if(m_axeVertical.Getx() == 1.0)
    {
        // Calcul des angles

		m_phi = std::asin(m_orientation.Getx());
		m_theta = std::acos(m_orientation.Gety() / std::cos(m_phi));

		if (m_orientation.Gety() < 0)
            m_theta *= -1;
    }


    // Si c'est l'axe Y

	else if (m_axeVertical.Gety() == 1.0)
    {
        // Calcul des angles

		m_phi = std::asin(m_orientation.Gety());
		m_theta = std::acos(m_orientation.Getz() / std::cos(m_phi));

		if (m_orientation.Getz() < 0)
            m_theta *= -1;
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des angles

		m_phi = std::asin(m_orientation.Getx());
		m_theta = std::acos(m_orientation.Getz() / std::cos(m_phi));

		if (m_orientation.Getz() < 0)
            m_theta *= -1;
    }


    // Conversion en degrés

    m_phi = m_phi * 180 / M_PI;
    m_theta = m_theta * 180 / M_PI;
}

void Camera::setPosition(Point2 position)
{
    m_position = position;

    // Actualisation du point ciblé
    m_pointCible = m_position + m_orientation;
}

