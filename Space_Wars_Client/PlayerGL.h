#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>


class PlayerGL
{
public:
	PlayerGL();
	PlayerGL(const PlayerGL& p){ *this = p; }
	~PlayerGL();

	bool operator== (PlayerGL const &p)
	{
		return p.id == this->id;
	}

	bool doRoation(float x, float y)
	{
		if (x != angleX || y != angleY)
		{
			angleX = x;
			angleY = y;
			orientation = glm::vec3(0, 1, 0);
			orientation = glm::rotateX(orientation, angleX);
			orientation = glm::rotateX(orientation, angleY);
			return true;
		}
		return false;
	}

	int getId(){return id;}
	void setId(int idd){ id = idd; }
	void updatePos(float micro)
	{
		float SPEED = 1000.0f;
		pos += orientation * SPEED * (micro / 1000.0f);
	}

	void moveBackward();

	glm::vec3 getPos() { return pos; }
	void setPos(float x, float y, float z){ pos.x = x; pos.y = y; pos.z = z; };
	void setPos(glm::vec3 p){ pos = p; }
	glm::vec3 getOrientation() { return orientation; }
	void setOrientation(glm::vec3 p){ orientation = p; }
	float getAngleX(){ return angleX; }
	float getAngleY(){ return angleY; }

protected:

	int id;
	glm::vec3 pos;
	glm::vec3 orientation;
	float angleX;
	float angleY;


	
};

