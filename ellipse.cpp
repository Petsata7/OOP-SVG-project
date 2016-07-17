#include "ellipse.h"
#include "rectangle.h"


Ellipse::Ellipse()
	: Circle()
	, ry(0.0)
{
	this->setType(ellipse);
}


Ellipse::Ellipse(const Ellipse& rhs)
	: Circle(rhs)
	, ry(rhs.ry)
{

}


Ellipse& Ellipse::operator = (const Ellipse & rhs)
{
	if (this == &rhs)
		return *this;

	Circle::operator=(rhs);
	ry = rhs.ry;

	return *this;
}


Ellipse::~Ellipse()
{

}


void Ellipse::setCoord(const double * coord, unsigned size)
{
	if (size < 4)
		return;


	center.setX(coord[0]);
	center.setY(coord[1]);

	if (coord[2] > 0)
		radius = coord[2];

	if (coord[3] > 0)
		ry = coord[3];


	setTopLeft( Point(center.getX() - radius, center.getY() - ry) );
	setBtmRight( Point(center.getX() + radius, center.getY() + ry) );


}


void Ellipse::translate(const Point& tr)
{
	center.translate(tr);


	setTopLeft(Point(center.getX() - radius, center.getY() - ry));
	setBtmRight(Point(center.getX() + radius, center.getY() + ry));
}


bool Ellipse::within(FigureType type, const double * coordinates, unsigned size)
{

	if (type == FigureType::rect)
	{
		if (size < 4)
			return false;

		Rectangle polygon;
		polygon.setCoord(coordinates, size);

		if ( !(center.getX() - radius >= polygon.getX() && center.getX() + radius <= polygon.getX() + polygon.getWidth()) )
			return false;

		if ( !(center.getY() - ry >= polygon.getY() && center.getY() + ry <= polygon.getY() + polygon.getHeight()) )
			return false;


		return true;
	}

	else if (type == FigureType::circle)
	{

		if (size < 3)
			return false;

		Circle polygon;
		polygon.setCoord(coordinates, size);

	

		if ( !(center.getX() - radius >= polygon.getX() - polygon.getRadius() && 
			center.getX() + radius <= polygon.getX() + polygon.getRadius() ))
			return false;

		if ( !(center.getY() - ry >= polygon.getY() - polygon.getRadius() &&
			center.getY() + ry <= polygon.getY() + polygon.getRadius() ))
			return false;

	

		return true;
	}


	return false;
}


void Ellipse::print()
{

	std::cout
		<< "ellipse "
		<< center << " " << radius	<< " " << ry << " "  << colours.getFill()	<< " "
		<< colours.getStroke()		<< " " << colours.getStrokeWidth()			<< '\n';
	
}

void Ellipse::writeToStream(std::ostream& os) const
{
	os
		<< "<ellipse "
		<< "cx=\""		<< center.getX()		<< "\" "
		<< "cy=\""		<< center.getY()		<< "\" "
		<< "rx=\""		<< radius				<< "\" "
		<< "ry=\""		<< ry					<< "\" "
		<< "fill=\""	<< colours.getFill()	<< "\" "
		<< "stroke=\""	<< colours.getStroke()	<< "\" ";

	if (colours.getStrokeWidth() > 1)
		os << "stroke-width=\"" << colours.getStrokeWidth() << "\" ";


	os << "/>\r\n";

}


const double Ellipse::getMax_Y()
{
	return center.getY() + ry + colours.getStrokeWidth();
}

