#ifndef MAT4X4_H
#define MAT4X4_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include "Point2.h"
#include <math.h>
#include <cmath>
#include <memory>

class Mat4x4
{
protected:
	float m[16];

public:
	Mat4x4(float val = 0);
	Mat4x4(Mat4x4& m2);
	~Mat4x4();

	Mat4x4& operator= (const Mat4x4& m2);
	Mat4x4& operator*=(const Mat4x4& m2);
	Mat4x4 operator* (const Mat4x4& m2);
	Point2& operator* ( Point2& p);
	float operator[] (const unsigned int i){ return m[i]; }

	float * getMatrix(){ return m; }

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void identity();
	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);
	void Orthographic(float L, float R, float T, float B, float N, float F);
	void Perspective(float FOV, float width, float height, float N, float F);
	void lookAt(Point2 position, Point2 target, Point2 up);
};
#endif
