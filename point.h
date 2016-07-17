#ifndef _POINT_HEADER_INCLUDED_
#define _POINT_HEADER_INCLUDED_


class Point
{

public:

	Point();
	Point(const Point& rhs);
	Point(double x, double y);
	Point& operator = (const Point& rhs);
	~Point();


	void translate(const Point& tr);

	void setX(double x);
	void setY(double y);

	const double getX() const { return x; }
	const double getY() const { return y; }


private:

	double x;
	double y;

};

#include <iostream>

std::ostream& operator << (std::ostream& os, const Point& p);

#endif //_POINT_HEADER_INCLUDED_