#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include "Shader.h"

class PlayerGL
{
public:
	PlayerGL();
	~PlayerGL();

	bool operator== (PlayerGL const &p)
	{
		return p.id == this->id;
	}

	void draw(glm::mat4 projection, glm::mat4 modelView);

	float* getVertices(){return vertices;}
	float* getColor(){return color;}




	int getId(){return id;}
	void setId(int idd){ id = idd; }

	glm::vec3 getPos() { return pos; }
	void setPos(float x, float y, float z){ pos.x = x; pos.y = y; pos.z = z; };
	void setPos(glm::vec3 p){ pos = p; }
	glm::vec3 getOrientation() { return orientation; }
	void setOrientation(glm::vec3 p){ orientation = p; }
	float getAngleX(){ return angleX; }
	void setAngleX(float a){ angleX = a; }
	float getAngleY(){ return angleY; }
	void setAngleY(float a){ angleY = a; }
	std::string getName(){return name;}
	void setName(std::string n){ name = n; }

protected:

	Shader m_shader;												

	GLuint m_vboID;							
	GLuint m_vaoID;		

	float vertices[15];

	float color[15];


	int id;
	glm::vec3 pos;
	glm::vec3 orientation;
	float angleX;
	float angleY;
	std::string name;


	
};

