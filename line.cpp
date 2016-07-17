#include "line.h"
#include "point.h"
#include "rectangle.h"



Line::Line()
	: Figure()
	, p1()
	, p2()
{

	this->setType(line);
}

Line::Line(const Line& rhs)
	: Figure(rhs)
	, p1(rhs.p1)
	, p2(rhs.p2)
{
	
}

Line& Line::operator = (const Line& rhs)
{
	if (this == &rhs)
		return *this;

	Figure::operator=(rhs);
	p1 = rhs.p1;
	p2 = rhs.p2;
	

	return *this; 
}

Line::~Line()
{
	
}


void Line::setCoord(const double * coord, unsigned size)
{
	if (size < 4)
		return;

	p1.setX(coord[0]);
	p1.setY(coord[1]);
	p2.setX(coord[2]);
	p2.setY(coord[3]);

	setTopLeft( Point( min(p1.getX(), p2.getX() ), min( p1.getY(), p2.getY()) ) );
	setBtmRight( Point( max(p1.getX(), p2.getX() ), max( p1.getY(), p2.getY()) ) );
}


void Line::setColours( const Colours_Manager& colours)
{
	
	this->colours.setStroke(colours.getStroke());

	this->colours.setStrokeWidth(colours.getStrokeWidth());
}


void Line::translate(const Point& tr)
{
	p1.translate(tr);
	p2.translate(tr);

	setTopLeft( Point( min(p1.getX(), p2.getX() ), min( p1.getY(), p2.getY()) ) );
	setBtmRight( Point( max(p1.getX(), p2.getX() ), max( p1.getY(), p2.getY()) ) );

}

bool Line::within(FigureType type, const double * coordinates, unsigned size)
{


	if (type == FigureType::rect)
	{

		if (size < 4)
			return false;

		Rectangle polygon;
		polygon.setCoord(coordinates, size);


		if ( !(p1.getX() >= polygon.getX() && p1.getX() <= polygon.getX() + polygon.getWidth()) )
			return false;

		if ( !(p2.getX() >= polygon.getX() && p2.getX() <= polygon.getX() + polygon.getWidth()) )
			return false;

		if ( !(p1.getY() >= polygon.getY() && p1.getY() <= polygon.getY() + polygon.getHeight()) )
			return false;

		if ( !(p2.getY() >= polygon.getY() && p2.getY() <= polygon.getY() + polygon.getHeight()) )
			return false;

		return true;
	}

	else if (type == FigureType::circle)
	{

		if (size < 3)
			return false;

		Circle polygon;
		polygon.setCoord(coordinates, size);

		double x = p1.getX() - polygon.getX();
		double y = p1.getY() - polygon.getY();
		double radius = polygon.getRadius();

		if ( !(x*x + y*y < radius*radius) )
			return false;


		x = p2.getX() - polygon.getX();
		y = p2.getY() - polygon.getY();
		
		if ( !(x*x + y*y < radius*radius) )
			return false;

		return true;
	}

	return false;
}


void Line::print()
{

	std::cout
		<< "line  "
		<< p1 << " " << p2 << " " << colours.getStroke() << " " << colours.getStrokeWidth() << '\n';
}

void Line::writeToStream(std::ostream& os) const
{

	os
		<< "<line "
		<< "x1=\""		<< p1.getX()			<< "\" "
		<< "y1=\""		<< p1.getY()			<< "\" "
		<< "x2=\""		<< p2.getX()			<< "\" "
		<< "y2=\""		<< p2.getY()			<< "\" "
		<< "stroke=\""	<< colours.getStroke()	<< "\" ";

	if (colours.getStrokeWidth() > 1)
		os << "stroke-width=\"" << colours.getStrokeWidth() << "\" ";


	os << "/>\r\n";

}


double Line::max(double a, double b)
{
	return (a > b) ? a : b;
}

double Line::min(double a, double b)
{
	return (a < b) ? a : b;
}


const double Line::getMax_X()
{
	return max( p1.getX(), p2.getX() ) + colours.getStrokeWidth();
}

const double Line::getMax_Y()
{
	return max( p1.getY(), p2.getY() ) + colours.getStrokeWidth();
}