#include "point.h"



Point::Point()
	: x(0.0)
	, y(0.0)
{

}


Point::Point(const Point& rhs)
	: x(rhs.x)
	, y(rhs.y)
{

}

Point::Point(double x, double y)
	: x(x)
	, y(y)
{

}

Point& Point::operator = (const Point& rhs)
{
	if (this == &rhs)
		return *this;

	x = rhs.x;
	y = rhs.y;

	return *this;
}

Point::~Point()
{

}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

void Point::translate(const Point& tr)
{
	x += tr.getX();
	y += tr.getY();
}


std::ostream& operator << (std::ostream& os, const Point& p)
{
	os << p.getX() << ' ' << p.getY();

	return os;

}
