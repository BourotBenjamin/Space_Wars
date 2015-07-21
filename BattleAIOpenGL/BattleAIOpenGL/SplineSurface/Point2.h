#ifndef POINT_H
#define POINT_H

#include <list>

class Point2
{
public:
	Point2();
	Point2(float x, float y, float z);
	Point2(const Point2 & p);
	~Point2();
	Point2 &operator=(const Point2 &p);
	int operator==(const Point2 &p) const;
	int operator!=(const Point2 &p) const;
	int operator<(const Point2 &p) const;

	Point2& operator+=(const Point2& p);
	Point2& operator*=(const Point2& p);
	Point2& operator*=(const float f);
	Point2& operator-=(const Point2& p);
	Point2& operator/=(const Point2& p);
	Point2& operator/=(const float f);

	static Point2 crossProduct(Point2 p1, Point2 p2);
	void normalize();

	static Point2 calcNormalInt(Point2 &F1, Point2 &F2, std::list<Point2> &list);
	static Point2 getVect(Point2 &P1, Point2 &P2);
	static float scalar(Point2 vect1, Point2 vect2);
	static bool isVisible(Point2 &P1, Point2 &F1, Point2 &F2, std::list<Point2> &list);
	static Point2 intersection(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2);
	static bool cut(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2, std::list<Point2> &list);
	static Point2& getNext(std::list<Point2>::iterator lit);
	static Point2& GetPoint(std::list<Point2> &l, int index);
	static std::list<Point2> SutherlandHodgman(std::list<Point2> &PW, std::list<Point2> &PL);
	static float getCdir(Point2 &P1, Point2 &P2);
	static float getMinY(std::list<Point2> &list);
	static float getMinX(std::list<Point2> &list);
	static float getMaxY(std::list<Point2> &list);
	static float getMaxX(std::list<Point2> &list);
	static bool cutStrict(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2);
	static bool isIntern(Point2 &P1, std::list<Point2> &list);

	float Getx() { return x; }
	void Setx(float val) { x = val; }
	float Gety() { return y; }
	void Sety(float val) { y = val; }
	float Getz() { return z; }
	void Setz(float val) { z = val; }

private:
	float x;
	float y;
	float z;
};

Point2 operator+(const Point2& p, const Point2& p2);
Point2 operator*(const Point2& p, const Point2& p2);
Point2 operator*(const Point2& p, const float f);
Point2 operator-(const Point2& p, const Point2& p2);
Point2 operator/(const Point2& p, const Point2& p2);
Point2 operator/(const Point2& p, const float f);


#endif // POINT_H
