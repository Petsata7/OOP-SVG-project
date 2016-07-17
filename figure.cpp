#include "figure.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "ellipse.h"
#include "polyline.h"
#include "polygon.h"

#include <string.h>
using std::nothrow;

Figure::Figure()
	: TL()
	, BR()
	, type(none)
	, colours()

{
	
}
Figure::Figure(const Figure& rhs)
	: TL(rhs.TL)
	, BR(rhs.BR)
	, type(rhs.type)
	, colours(rhs.colours)
{
}

Figure& Figure::operator = (const Figure& rhs)
{
	if (this == &rhs)
		return *this;

	TL = rhs.TL;
	BR = rhs.BR;
	type = rhs.type;
	colours = rhs.colours;

	return *this;

}

Figure:: ~Figure()
{

}

void Figure::swapIfNeeded()
{

	if (TL.getX() > BR.getX())
	{
		double x = TL.getX();
		TL.setX(BR.getX());
		BR.setX(x);
	}

	if (TL.getY() > BR.getY())
	{
		double y = TL.getY();
		TL.setY(BR.getY());
		BR.setX(y);
	}

}

void Figure::setTopLeft(const Point& point)
{
	TL = point;
	swapIfNeeded();
}

void Figure::setBtmRight(const Point& point)
{
	BR = point;
	swapIfNeeded();
}


void Figure::setType(FigureType type)
{
	this->type = type;
}


Figure* Figure::createFigure(FigureType type)
{


	switch (type)
	{
		case	rect:		return new (nothrow) Rectangle;
		case	circle:		return new (nothrow) Circle;
		case	line:		return new (nothrow) Line;
		case	ellipse:	return new (nothrow) Ellipse;
		case	polyline:	return new (nothrow) Polyline;
		case	polygon:	return new (nothrow) Polygon;
		default:			return NULL;

	}

}

const char * Figure::getName() const
{

	switch (this->type)
	{
		case	rect:		return "rectangle";
		case	circle:		return "circle";
		case	line:		return "line";
		case	ellipse:	return "ellipse";
		case	polyline:	return "polyline";
		case	polygon:	return "polygon";
		default:			return "none";
	}


}

std::ostream& operator << (std::ostream& os, const Figure& fig)
{

	fig.writeToStream( os );

	return os;
}