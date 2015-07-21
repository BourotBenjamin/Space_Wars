#pragma once

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>

static const float g_pyramydeVertices[] = {
	-1.f, -1.f, 1.0f,		// 0
	1.f, 0.f, 0.0f,  		// 1
	-1.f, 1.f, 1.0f,		// 3	
	-1.f, -1.f, -1.0f,		// 4
	-1.f, 1.f, -1.0f		// 7
};

static const unsigned short g_pyramideIndices[] = {

	3, 0, 2, // gauche
	2, 4, 3,
	0, 1, 2,
	2, 1, 4,
	4, 1, 2,
	3, 1, 0
};

class PlayerGL
{
public:
	PlayerGL();
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

	void draw(glm::mat4& projection, glm::mat4& modelView);
	void draw(float * projection, float * modelView);

	float* getVertices(){return vertices;}
	float* getColor(){return color;}

	void load();


	int getId(){return id;}
	void setId(int idd){ id = idd; }
	void updatePos(float micro)
	{
		float SPEED = 1000.0f;
		pos += orientation * SPEED * (micro / 1000.0f);
	}

	glm::vec3 getPos() { return pos; }
	void setPos(float x, float y, float z){ pos.x = x; pos.y = y; pos.z = z; };
	void setPos(glm::vec3 p){ pos = p; }
	glm::vec3 getOrientation() { return orientation; }
	void setOrientation(glm::vec3 p){ orientation = p; }
	float getAngleX(){ return angleX; }
	float getAngleY(){ return angleY; }
	std::string getName(){return name;}
	void setName(std::string n){ name = n; }

protected:

	Shader m_shader;												

	GLuint m_vboID;							
	GLuint m_vaoID;	
	GLuint m_eboID;

	float vertices[15];

	float color[15];

	GLushort indices[18];

	glm::mat4 rotation;

	int id;
	glm::vec3 pos;
	glm::vec3 orientation;
	float angleX;
	float angleY;
	std::string name;


	
};

