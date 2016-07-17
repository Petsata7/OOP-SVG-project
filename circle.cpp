#include "circle.h"
#include "rectangle.h"

Circle::Circle()
	: Figure()
	, center()
	, radius(0.0)
{
	
	this->setType(circle);

}

Circle::Circle(const Circle& rhs)
	: Figure(rhs)
	, center(rhs.center)
	, radius(rhs.radius)
{
	
}

Circle& Circle::operator = (const Circle & rhs)
{
	if (this == &rhs)
		return *this;

	Figure::operator=(rhs);
	center = rhs.center;
	radius = rhs.radius;
	

	return *this;
}

Circle::~Circle()
{

}


void Circle::setCoord(const double * coord, unsigned size)
{

	if (size < 3)
		return;
	
	center.setX(coord[0]);
	center.setY(coord[1]);

	if (coord[2] > 0)
		radius = coord[2];


	setTopLeft( Point(center.getX() - radius, center.getY() - radius) );
	setBtmRight( Point(center.getX() + radius, center.getY() + radius) );


}

void Circle::setColours(const Colours_Manager& colours)
{
	
	this->colours.setFill(colours.getFill());

	this->colours.setStroke(colours.getStroke());

	this->colours.setStrokeWidth(colours.getStrokeWidth());
}


void Circle::translate(const Point& tr)
{
	center.translate(tr);

	setTopLeft( Point(center.getX() - radius, center.getY() - radius) );
	setBtmRight( Point(center.getX() + radius, center.getY() + radius) );

}

bool Circle::within(FigureType type, const double * coordinates, unsigned size)
{

	

	if (type == FigureType::rect)
	{
		if (size < 4)
			return false;

		Rectangle polygon;
		polygon.setCoord(coordinates, size);

		if ( !(center.getX() - radius >= polygon.getX() && center.getX() + radius <= polygon.getX() + polygon.getWidth()) )
			return false;

		if ( !(center.getY() - radius >= polygon.getY() && center.getY() + radius <= polygon.getY() + polygon.getHeight()) )
			return false;


		return true;
	}

	else if (type == FigureType::circle)
	{

		if (size < 3)
			return false;

		Circle polygon;
		polygon.setCoord(coordinates, size);

		double distX = polygon.getX() - center.getX();
		double distY = polygon.getY() - center.getY();
		double radiusDifference = polygon.getRadius() - radius;

		if (radiusDifference < 0)
			return false;

		if ( !(distX*distX + distY*distY <= radiusDifference*radiusDifference) )
			return false;


		return true;
	}


	return false;
}


void Circle::print()
{
	std::cout
		<< "circle "
		<< center << " " << radius	<< " " << colours.getFill() 		<< " " 
		<< colours.getStroke()		<< " " << colours.getStrokeWidth() 	<< '\n';

}

void Circle::writeToStream(std::ostream& os) const
{
	os
		<< "<circle "
		<< "cx=\""		<< center.getX()			<< "\" "
		<< "cy=\""		<< center.getY()			<< "\" "
		<< "r=\""		<< radius				<< "\" "
		<< "fill=\""		<< colours.getFill()			<< "\" "
		<< "stroke=\""		<< colours.getStroke()			<< "\" ";

	if (colours.getStrokeWidth() > 1)
		os << "stroke-width=\"" << colours.getStrokeWidth() << "\" ";


		os << "/>\r\n"; 

}

const double Circle::getMax_X()
{	
	return center.getX() + radius + colours.getStrokeWidth();
}

const double Circle::getMax_Y()
{
	return center.getY() + radius + colours.getStrokeWidth();
}
