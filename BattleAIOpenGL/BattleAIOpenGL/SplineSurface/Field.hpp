#ifndef _FIELD_HPP_
#define _FIELD_HPP_

class Field
{
protected:

	static Field m_instance;

	int width;
	int height;



public:
	static Field& getInstance(){ return m_instance; }
	
	int getW(){ return width; }
	int getH(){ return height; }

	void setW(int w){ width = w; }
	void setH(int h){ height = h; }

	Point clamp(Point p)
	{
		Point ret = p;
		if (p.getX() >= width)
			ret.setX(width);
		else if (p.getX() <= 0)
			ret.setX(0);
		if (p.getY() >= height)
			ret.setY(height);
		else if (p.getY() <= 0)
			ret.setY(0);

		return ret;
	}
};


#endif