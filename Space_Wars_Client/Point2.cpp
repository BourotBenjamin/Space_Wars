
#include "Point2.h"
Point2::Point2()
{
	x = 0.;
	y = 0.;
	z = 0.;
}

Point2::~Point2()
{

}

Point2::Point2(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point2::Point2(const Point2 & p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

Point2& Point2::operator=(const Point2 &p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	return *this;
}

int Point2::operator==(const Point2 &p) const
{
	if (this->x != p.x) return 0;
	if (this->y != p.y) return 0;
	if (this->z != p.z) return 0;
	return 1;
}

int Point2::operator!=(const Point2 &p) const
{
	if ((this->x == p.x) && (this->y == p.y) && (this->z == p.z))return 0;
	return 1;
}

int Point2::operator<(const Point2 &p) const
{
	if (this->x == p.x && this->y < p.y) return 1;
	if (this->x < p.x) return 1;
	return 0;
}

Point2& Point2::operator+=(const Point2& p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

Point2 operator+(const Point2& p, const Point2& p2)
{
	Point2 cpy(p);
	cpy += p2;
	return cpy;
}

Point2& Point2::operator*=(const Point2& p)
{
	x *= p.x;
	y *= p.y;
	z *= p.z;
	return *this;
}

Point2& Point2::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Point2 operator*(const Point2& p, const Point2& p2)
{
	Point2 cpy(p);
	cpy *= p2;
	return cpy;
}

Point2 operator*(const Point2& p, const float f)
{
	Point2 cpy(p);
	cpy *= f;
	return cpy;
}

Point2& Point2::operator-=(const Point2& p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

Point2 operator-(const Point2& p, const Point2& p2)
{
	Point2 cpy(p);
	cpy -= p2;
	return cpy;
}

Point2& Point2::operator/=(const Point2& p)
{
	x /= p.x;
	y /= p.y;
	z /= p.z;
	return *this;
}

Point2& Point2::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

Point2 operator/(const Point2& p, const float f)
{
	Point2 cpy(p);
	cpy /= f;
	return cpy;
}


Point2 Point2::calcNormalInt(Point2 &F1, Point2 &F2, std::list<Point2> &list)
{
	Point2 seg = getVect(F1, F2);
	Point2 P3;
	std::list<Point2>::iterator lit;
	for (lit = list.begin(); lit != list.end(); ++lit)
	{
		if (*lit == F1 || *lit == F2)
			continue;
		else
		{
			P3 = *lit;
			break;
		}
	}
	Point2 vect = getVect(F1, P3);
	Point2 normal1(-seg.y, seg.x, 0);
	Point2 normal2(seg.y, -seg.x, 0);
	if (0 < scalar(vect, normal1)) //if true normal1 is interne
		return normal1;
	else
		return normal2;
}

Point2 Point2::getVect(Point2 &P1, Point2 &P2)
{
	float x = (P2.x - P1.x);
	float y = (P2.y - P1.y);
	float z = (P2.z - P1.z);
	Point2 v(x, y, z);
	return v;
}

float Point2::scalar(Point2 vect1, Point2 vect2)
{
	return (vect1.x * vect2.x) + (vect1.y*vect2.y)+ (vect1.z * vect2.z);
}

Point2 Point2::crossProduct(Point2 p1, Point2 p2)
{
	Point2 p = Point2();
	p.x = p1.y*p2.z - p2.y*p1.z;
	p.y = p1.z*p2.x - p2.z*p1.x;
	p.z = p1.x*p2.y - p2.x*p1.y;
	return p;
}

void Point2::normalize()
{
	(*this) /= std::sqrtf((x*x)+(y*y)+(z*z));
}

bool Point2::isVisible(Point2 &P1, Point2 &F1, Point2 &F2, std::list<Point2> &list)
{
	bool res = false;
	Point2 P1F1 = getVect(F1, P1);
	Point2 n = calcNormalInt(F1, F2, list);
	//if scalar * normal is over 0 then return true
	if (scalar(n, P1F1) > 0)
		res = true;
	return res;
}

Point2 Point2::intersection(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2)
{
	Point2 p;
	float s = 0;
	float t = 0;
	float numS = ((P1.y - F1.y)*(P2.x - P1.x) - (P1.x - F1.x)*(P2.y - P1.y));
	float numT = ((P1.y - F1.y)*(F2.x - F1.x) - (P1.x - F1.x)*(F2.y - F1.y));
	float denominator = ((P2.x - P1.x)*(F2.y - F1.y) - (P2.y - P1.y)*(F2.x - F1.x));
	if (0 != denominator || 0 != numS)
	{
		t = numT / denominator;
		s = numS / denominator;
		if ((0 <= t && 1 >= t) && (0 <= s && 1 >= s))
		{
			p = Point2((P1.x + (t*(P2.x - P1.x))), (P1.y + (t*(P2.y - P1.y))), 0);
			return p;
		}
		else if ((1 < s || 0 > s) && (0 <= t && 1 >= t))
		{
			p = Point2((P1.x + (t*(P2.x - P1.x))), (P1.y + (t*(P2.y - P1.y))), 0);
			return p;
		}
	}
	return p;
}

bool Point2::cut(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2, std::list<Point2> &list)
{
	bool P1visible = isVisible(P1, F1, F2, list);
	bool P2visible = isVisible(P2, F1, F2, list);
	if ((P1visible && !P2visible) || (P2visible && !P1visible)){
		return true;
	}
	return false;
}

Point2& Point2::getNext(std::list<Point2>::iterator lit)
{
	std::list<Point2>::iterator nit = lit;
	++nit;
	return *nit;
}

Point2& Point2::GetPoint(std::list<Point2> &l, int index)
{
	std::list<Point2>::iterator lit = l.begin();
	std::advance(lit, index);
	return (*lit);
}

std::list<Point2> Point2::SutherlandHodgman(std::list<Point2> &PW, std::list<Point2> &PL)
{
	std::list<Point2>PTD = PL; 
	std::list<Point2>PS;
	Point2 first;
	Point2 I;
	Point2 S;
	int i = 0, j = 0;
	std::list<Point2>::iterator wit;
	std::list<Point2>::iterator pit;
	for (wit = PW.begin(); wit != PW.end(); ++wit)
	{
		j = 0;
		for (pit = PTD.begin(); pit != PTD.end(); ++pit)
		{
			if (0 == j)
				first = *pit;
			else
			{
				Point2 next;
				if (*wit == PW.back())
					next = PW.front();
				else
					next = getNext(wit);

				if (cut(S, *pit, *wit, next, PW))
				{
					I = intersection(S, *pit, *wit, next);
					PS.push_back(I);
				}
			}
			S = *pit; 
			Point2 next;
			if (*wit == PW.back())
				next = PW.front();
			else
				next = getNext(wit);
			if (isVisible(S, *wit, next, PW))
				PS.push_back(S);

			j++;
		}
		if (!PS.empty())
		{
			Point2 next;
			if (*wit == PW.back())
				next = PW.front();
			else
				next = getNext(wit);

			if (cut(S, first, *wit, next, PW))
			{
				I = intersection(S, first, *wit, next);
				PS.push_back(I);
			}
			PTD = PS;
			PS.clear();
		}
		else
			PTD.clear();

		i++;
	}
	return PTD;
}

float Point2::getCdir(Point2 &P1, Point2 &P2){
	return ((P2.y - P1.y) / (P2.x - P1.x));
}

float Point2::getMinY(std::list<Point2> &list)
{
	if (list.empty())
		return NULL;

	float Ymin = list.front().Gety();
	std::list<Point2>::iterator lit;
	for (lit = list.begin(); lit != list.end(); ++lit)
	if ((*lit).Gety() < Ymin)
		Ymin = (*lit).Gety();

	return Ymin;
}

float Point2::getMinX(std::list<Point2> &list)
{
	if (list.empty())
		return NULL;

	float Xmin = list.front().Gety();
	std::list<Point2>::iterator lit;
	for (lit = list.begin(); lit != list.end(); ++lit)
	if ((*lit).Getx() < Xmin)
		Xmin = (*lit).Getx();

	return Xmin;
}

float Point2::getMaxY(std::list<Point2> &list)
{
	if (list.empty())
		return NULL;

	float Ymax = list.front().Gety();
	std::list<Point2>::iterator lit;
	for (lit = list.begin(); lit != list.end(); ++lit)
	if ((*lit).Gety() > Ymax)
		Ymax = (*lit).Gety();

	return Ymax;
}

float Point2::getMaxX(std::list<Point2> &list)
{
	if (list.empty())
		return NULL;

	float Xmax = list.front().Gety();
	std::list<Point2>::iterator lit;
	for (lit = list.begin(); lit != list.end(); ++lit)
	if ((*lit).Getx() > Xmax)
		Xmax = (*lit).Getx();

	return Xmax;
}

bool Point2::cutStrict(Point2 &P1, Point2 &P2, Point2 &F1, Point2 &F2)
{
	float s = 0;
	float t = 0;
	float numS = ((P1.y - F1.y)*(P2.x - P1.x) - (P1.x - F1.x)*(P2.y - P1.y));
	float numT = ((P1.y - F1.y)*(F2.x - F1.x) - (P1.x - F1.x)*(F2.y - F1.y));
	float denominator = ((P2.x - P1.x)*(F2.y - F1.y) - (P2.y - P1.y)*(F2.x - F1.x));
	if (0 != denominator || 0 != numS)//If denominator is zero,[P1P2] & [F1F2] are parallel || If the numS equals zero, [P1P2] & [F1F2] are coincident
	{
		t = numT / denominator;
		s = numS / denominator;
		if ((0 <= t && 1 >= t) && (0 <= s && 1 >= s))
			return true;
	}
	return false;
}

bool Point2::isIntern(Point2 &P1, std::list<Point2> &list)
{
	Point2 I;                                                        
	Point2 P2 = Point2(getMaxX(list) + 10, P1.Gety(), 0);             
	int nbIntersecs = 0, i = 0;                                     
	bool added = false;                                             
	std::list<Point2>::iterator lit;                                 
	for (lit = list.begin(); lit != list.end(); ++lit)          
	{
		Point2 next;
		if (*lit == list.back())
			next = list.front();
		else
			next = getNext(lit); 
		if (cutStrict(P1, P2, *lit, next))                                        
		{
			I = Point2::intersection(P1, P2, *lit, next);                          
			if (I == *lit)                                                        
				added = true;                                                    
			else if (I == next)                                                  
			{
				Point2 S1 = *lit;
				int n = (i + 1 >= list.size()) ? 1 : (i + 2 >= list.size()) ? 0 : i + 2;
				Point2 S2 = GetPoint(list, n);
				if ((S1.Gety() > I.Gety() && S2.Gety() < I.Gety()) || (S1.Gety() < I.Gety() && S2.Gety() > I.Gety()))
					nbIntersecs++;                                                                                   
				else                                                                                                  
					nbIntersecs += 2;                                                                                 

				added = true;                                                                             
			}
			if (!added)      
				nbIntersecs++; 
		}
		i++;
		added = false;          
	}

	return !(0 == nbIntersecs % 2);
}
