#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include "Point2.h"
#include <math.h>
#include <cmath>
#include <memory>
#define GLEW_STATIC 1
#include <GL\glew.h>
#include "Shader.h"
#include "Mat4x4.h"
#include "projectileInfo.h"

class ProjectileGL
{
public:
	ProjectileGL(std::string vs, std::string fs);
	~ProjectileGL();

	void load();
	void draw(Mat4x4 projection, Mat4x4 modelView, Mat4x4 world, Point2 color, Point2 camPos, Point2 camDir);

protected:

	Shader m_shader;
	int vbosize;
	int ebosize;

	GLuint m_vboID;
	GLuint m_vaoID;
	GLuint m_triangleEBO;

	std::vector<float> m_toVBOPoints;
	std::vector<float> m_toVBOColors;
	std::vector<GLushort> m_indicesTriangle;
};