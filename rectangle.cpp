#include "rectangle.h"


Rectangle::Rectangle()
	: Figure()
	, p()
	, width(0)
	, height(0)
	, rx(0)
	, ry(0)
{
	
	this->setType(rect);
}

Rectangle::Rectangle(const Rectangle& rhs)
	: Figure(rhs)
	, p(rhs.p)
	, width(rhs.width)
	, height(rhs.height)
	, rx(rhs.rx)
	, ry(rhs.ry)
{
	
}

Rectangle& Rectangle::operator = (const Rectangle& rhs)
{

	if (this == &rhs)
		return *this;

	
	Figure::operator=(rhs);
	p = rhs.p;
	width = rhs.width;
	height = rhs.height;
	rx = rhs.rx;
	ry = rhs.ry;	
	

		
	return *this;

}

Rectangle::~Rectangle()
{
	
}

void Rectangle::setCoord(const double * coord, unsigned size)
{
	if (size < 4)
		return;


	p.setX(coord[0]);
	p.setY(coord[1]);
	
	width = coord[2];
	height = coord[3];
	

	if (size > 5)
	{
		rx = coord[4];
		ry = coord[5];
	}

	if (height < 0)
		height = 0;

	if (width < 0)
		width = 0;
	
	if (rx < 0)
		rx = 0;

	if (ry < 0)
		ry = 0;


	setTopLeft( Point(p.getX(), p.getY()));
	setBtmRight( Point(p.getX() + width, p.getY() + height) );

}

void Rectangle::setColours(const Colours_Manager& colours)
{
	this->colours.setFill(colours.getFill());

	this->colours.setStroke(colours.getStroke());

	this->colours.setStrokeWidth(colours.getStrokeWidth());

}

void Rectangle::translate(const Point& tr)
{
	p.translate(tr);

	setTopLeft( Point(p.getX(), p.getY()) );
	setBtmRight( Point(p.getX() + width, p.getY() + height) );

}


bool Rectangle::within(FigureType type, const double * coordinates, unsigned size)
{
	

	if (type == FigureType::rect)
	{
		if (size < 4)
			return false;

		Rectangle polygon;
		polygon.setCoord(coordinates, size);

		if ( !(p.getX() >= polygon.getX() && p.getX() + width <= polygon.getX() + polygon.getWidth()) )
			return false;

		if ( !(p.getY() >= polygon.getY() && p.getY() + height <= polygon.getY() + polygon.getHeight()) )
			return false;

		return true;
	}

	else if (type == FigureType::circle)
	{
		if (size < 3)
			return false;

		Circle polygon;
		polygon.setCoord(coordinates, size);

		double distX = max( (polygon.getX() - p.getX())*(polygon.getX() - p.getX()) , 
			(polygon.getX() - p.getX() + width)*(polygon.getX() - p.getX() + width) );

		double distY = max( (polygon.getY() - p.getY())*(polygon.getY() - p.getY()) ,
			(polygon.getY() - p.getY() + height)*(polygon.getY() - p.getY() + height) );

		if ( !( distX + distY <= polygon.getRadius()*polygon.getRadius()) ) //distances are already squared
			return false;

		return true;
	}

	return false;
}

void Rectangle::print()
{
	
	std::cout
		<< "rectangle "
		<< p << " " << width << " " << height << " "
		<< colours.getFill() << " " << colours.getStroke() << " " << colours.getStrokeWidth() << '\n';

}

void Rectangle::writeToStream(std::ostream& os) const
{
	os
		<< "<rect "
		<< "x=\""			<< p.getX()				<< "\" "
		<< "y=\""			<< p.getY()				<< "\" " 
		<< "width=\""			<< width				<< "\" "
		<< "height=\""			<< height				<< "\" "
		<< "rx=\""			<< rx					<< "\" "
		<< "ry=\""			<< ry					<< "\" "
		<< "fill=\""			<< colours.getFill()			<< "\" "
		<< "stroke=\""			<< colours.getStroke()			<< "\" ";
		

	if (colours.getStrokeWidth() > 1)
		os << "stroke-width=\"" << colours.getStrokeWidth() << "\" ";

	os << "/>\r\n";
	

}


double Rectangle::max(double a, double b)
{
	return (a > b) ? a : b;
}


const double Rectangle::getMax_X() 
{
	return p.getX() + width + colours.getStrokeWidth();
}

const double Rectangle::getMax_Y() 
{
	return p.getY() + height + colours.getStrokeWidth();
}
