#include "Mat4x4.h"


Mat4x4::Mat4x4(float val)
{
	memset(m, val, sizeof(float)* 16);
}

Mat4x4::Mat4x4(Mat4x4& m2)
{
	for(int i = 0; i < 16; i++)
		m[i] = m2.m[i];
}

Mat4x4::~Mat4x4()
{
}

Mat4x4& Mat4x4::operator= (const Mat4x4& m2)
{
	for(int i = 0; i < 16; i++)
		m[i] = m2.m[i];
	return (*this);
}

Mat4x4& Mat4x4::operator*= (const Mat4x4& m2)
{
	m[0] = m[0] * m2.m[0] + m[4] * m2.m[1] + m[8] * m2.m[2] + m[12] * m2.m[3];
	m[1] = m[1] * m2.m[0] + m[5] * m2.m[1] + m[9] * m2.m[2] + m[13] * m2.m[3];
	m[2] = m[2] * m2.m[0] + m[6] * m2.m[1] + m[10] * m2.m[2] + m[14] * m2.m[3];
	m[3] = m[3] * m2.m[0] + m[7] * m2.m[1] + m[11] * m2.m[2] + m[15] * m2.m[3];

	m[4] = m[0] * m2.m[4] + m[4] * m2.m[5] + m[8] * m2.m[6] + m[12] * m2.m[7];
	m[5] = m[1] * m2.m[4] + m[5] * m2.m[5] + m[9] * m2.m[6] + m[13] * m2.m[7];
	m[6] = m[2] * m2.m[4] + m[6] * m2.m[5] + m[10] * m2.m[6] + m[14] * m2.m[7];
	m[7] = m[3] * m2.m[4] + m[7] * m2.m[5] + m[11] * m2.m[6] + m[15] * m2.m[7];

	m[8] = m[0] * m2.m[8] + m[4] * m2.m[9] + m[8] * m2.m[10] + m[12] * m2.m[11];
	m[9] = m[1] * m2.m[8] + m[5] * m2.m[9] + m[9] * m2.m[10] + m[13] * m2.m[11];
	m[10] = m[2] * m2.m[8] + m[6] * m2.m[9] + m[10] * m2.m[10] + m[14] * m2.m[11];
	m[11] = m[3] * m2.m[8] + m[7] * m2.m[9] + m[11] * m2.m[10] + m[15] * m2.m[11];

	m[12] = m[0] * m2.m[12] + m[4] * m2.m[13] + m[8] * m2.m[14] + m[12] * m2.m[15];
	m[13] = m[1] * m2.m[12] + m[5] * m2.m[13] + m[9] * m2.m[14] + m[13] * m2.m[15];
	m[14] = m[2] * m2.m[12] + m[6] * m2.m[13] + m[10] * m2.m[14] + m[14] * m2.m[15];
	m[15] = m[3] * m2.m[12] + m[7] * m2.m[13] + m[11] * m2.m[14] + m[15] * m2.m[15];

	return (*this);
}

Point2& Mat4x4::operator* (Point2& p)
{
	Point2 ret = Point2();

	ret.Setx(m[0] * p.Getx() + m[4] * p.Gety() + m[8] * p.Getz());
	ret.Sety(m[1] * p.Getx() + m[5] * p.Gety() + m[9] * p.Getz());
	ret.Setz(m[2] * p.Getx() + m[6] * p.Gety() + m[10] * p.Getz());

	return ret;
}

Mat4x4 Mat4x4::operator* (const Mat4x4& m2)
{
	Mat4x4 ret = Mat4x4(*this);

	/*for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			ret.m[(j * 4) + i] = m[i] * m2.m[(j * 4)] + m[i + 4] * m2.m[(j * 4) + 1] + m[i + 8] * m2.m[(j * 4) + 2] + m[i + 12] * m2.m[(j * 4) + 3];
		}
	}*/
	return ret*=m2;
}

void Mat4x4::identity()
{
	memset(m, 0, sizeof(float)* 16);
	m[0] = 1.0f; m[5] = 1.0f; m[10] = 1.0f; m[15] = 1.0f;
}

void Mat4x4::translate(float x, float y, float z)
{
	Mat4x4 matrix = Mat4x4();
	matrix.identity();
	matrix.m[12] = x;
	matrix.m[13] = y;
	matrix.m[14] = z;

	(*this) *= matrix;
}

void Mat4x4::rotateX(float angle)
{
	Mat4x4 matrix = Mat4x4();
	float angleRad = angle*M_PI / 180;
	matrix.identity();
	matrix.m[5] = std::cosf(angleRad);
	matrix.m[6] = std::sinf(angleRad);
	matrix.m[9] = -std::sinf(angleRad);
	matrix.m[10] = std::cosf(angleRad);

	(*this) *= matrix;
}

void Mat4x4::rotateY(float angle)
{
	Mat4x4 matrix = Mat4x4();
	float angleRad = angle*M_PI / 180;
	matrix.identity();
	matrix.m[0] = std::cosf(angleRad);
	matrix.m[2] = std::sinf(angleRad);
	matrix.m[8] = -std::sinf(angleRad);
	matrix.m[10] = std::cosf(angleRad);

	(*this) *= matrix;
}

void Mat4x4::rotateZ(float angle)
{
	Mat4x4 matrix = Mat4x4();
	float angleRad = angle*M_PI / 180;
	matrix.identity();
	matrix.m[0] = std::cosf(angleRad);
	matrix.m[1] = std::sinf(angleRad);
	matrix.m[4] = -std::sinf(angleRad);
	matrix.m[5] = std::cosf(angleRad);

	(*this) *= matrix;
}

void Mat4x4::rotate(float angle, float x, float y, float z)
{
	Mat4x4 matrix = Mat4x4();
	matrix.identity();
	float cos = std::cosf(angle);
	float sin = std::sinf(angle);
	matrix.m[0] = x * x * (1 - cos) + cos;
	matrix.m[1] = x * y * (1 - cos) + z * sin;
	matrix.m[2] = x * z * (1 - cos) - y * sin;
	matrix.m[4] = y * x * (1 - cos) - z * sin;
	matrix.m[5] = y * y * (1 - cos) + cos;
	matrix.m[6] = y * z * (1 - cos) + x * sin;
	matrix.m[8] = z * x * (1 - cos) + y * sin;
	matrix.m[9] = z * y * (1 - cos) - x * sin;
	matrix.m[10] = z * z * (1 - cos) + cos;

	(*this) *= matrix;
}

void Mat4x4::scale(float x, float y, float z)
{
	Mat4x4 matrix = Mat4x4();
	matrix.identity();
	matrix.m[0] = x;
	matrix.m[5] = y;
	matrix.m[10] = z;

	(*this) *= matrix;
}

void Mat4x4::Orthographic(float L, float R, float T, float B, float N, float F)
{
	memset(m, 0, sizeof(float)* 16);
	m[0] = 2.f / (R - L);
	m[5] = 2.f / (T - B);
	m[10] = -2.f / (F - N);
	m[12] = -(R + L) / (R - L);
	m[13] = -(T + B) / (T - B);
	m[14] = -(F + N) / (F - N);
	m[15] = 1.f;
}

void Mat4x4::Perspective(float FOV, float width, float height, float N, float F)
{
	memset(m, 0, sizeof(float)* 16);
	float aspect = width / height;

	float xymax = N * tan(FOV * (3.141592f / 180.f) * 0.5f);
	float ymin = -xymax;
	float xmin = -xymax;
	width = xymax - xmin;
	height = xymax - ymin;
	float depth = F - N;
	float q = -(F + N) / depth;
	float qn = -2.0f * (F*N) / depth;

	float w = 2.0f * N / width;
	w = w / aspect;
	float h = 2.0f * N / height;

	m[0] = w;
	m[5] = h;
	m[10] = q;
	m[11] = -1.f;
	m[14] = qn;
}

void Mat4x4::lookAt(Point2 position, Point2 target, Point2 up)
{
	identity();
	Point2 direction = target - position;
	direction.normalize();
	up.normalize();

	Point2 s = Point2::crossProduct(direction, up);
	Point2 u = Point2::crossProduct(s, direction);

	m[0]  = s.Getx();
	m[1]  = u.Getx();
	m[2]  = -direction.Getx();
	m[4]  = s.Gety();
	m[5]  = u.Gety();
	m[6]  = -direction.Gety();
	m[8]  = s.Getz();
	m[9]  = u.Getz();
	m[10] = -direction.Getz();

	translate(-position.Getx(), -position.Gety(), -position.Getz());
}
