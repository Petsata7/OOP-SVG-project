#include "polyline.h"
#include "rectangle.h"
#include "circle.h"

Polyline::Polyline()
	: Figure()
	, size(0)
	, point(NULL)
{

	this->setType(polyline);

}



Polyline::Polyline(const Polyline& rhs)
{
	copy(rhs);
}


Polyline& Polyline::operator = (const Polyline& rhs)
{

	if (this == &rhs)
		return *this;

	clear();
	copy(rhs);

	return *this;

}

Polyline::~Polyline()
{
	clear();
}


void Polyline::setCoord(const double * coord, unsigned size)
{

	if (resize(size / 2))
	{

		unsigned k = 0;

		for (unsigned i = 0; i < this->size; ++i)
		{

			if (k >= size)
				break;

			point[i].setX(coord[k++]);

			if (k >= size)
				break;

			point[i].setY(coord[k++]);

		}
	}


	setTopLeft( Point(getMin_X(), getMin_Y()) );
	setBtmRight( Point(getMax_X(),getMax_Y()) );


}

void Polyline::setColours(const Colours_Manager& colours)
{
	this->colours.setFill(colours.getFill());

	this->colours.setStroke(colours.getStroke());

	this->colours.setStrokeWidth(colours.getStrokeWidth());

}



void Polyline::translate(const Point& tr)
{
	
	for (unsigned i = 0; i < size; ++i)
		point[i].translate(tr);
	


	setTopLeft( Point(getMin_X(), getMin_Y()) );
	setBtmRight( Point(getMax_X(), getMax_Y()) );

}


bool Polyline::within(FigureType type, const double * coordinates, unsigned size)
{



	if (type == FigureType::rect)
	{

		if (size < 4)
			return false;

		Rectangle polygon;
		polygon.setCoord(coordinates, size);


		for (unsigned i = 0; i < this->size; ++i) 
		{

			if ( !(point[i].getX() >= polygon.getX() && point[i].getX() <= polygon.getX() + polygon.getWidth()) )
				return false;

			if ( !(point[i].getY() >= polygon.getY() && point[i].getY() <= polygon.getY() + polygon.getHeight()) )
				return false;

		}


		return true;

	}

	else if (type == FigureType::circle)
	{

		if (size < 3)
			return false;

		Circle polygon;
		polygon.setCoord(coordinates, size);

	
		double distX; 
		double distY; 
		double radius = polygon.getRadius();


		for (unsigned i = 0; i < this->size; ++i)
		{
			distX = point[i].getX() - polygon.getX();
			distY = point[i].getY() - polygon.getY();
			
			if ( !(distX*distX + distY*distY < radius*radius) )
				return false;
		}


		return true;
	}


	return false;
}


void Polyline::print()
{

	std::cout
		<< "polyline "
		<< colours.getFill() << " " << colours.getStroke() << " " << colours.getStrokeWidth() << ' ';

	for (unsigned i = 0; i < size; ++i)
		std::cout << point[i] << ' ';

	std::cout << '\n';

}

void Polyline::writeToStream(std::ostream& os) const
{
	os
		<< "<polyline "
		<< "fill=\""	<< colours.getFill()	<< "\" "
		<< "stroke=\""	<< colours.getStroke()	<< "\" ";


	if (colours.getStrokeWidth() > 1)
		os << "stroke-width=\"" << colours.getStrokeWidth() << "\" ";

	os << "points=\"";


	for (unsigned i = 0; i < size; ++i)
	{
		os << ' ' << point[i].getX() << ',' << point[i].getY() << ' ';
	}

	os << " \" />\r\n";


}

const double Polyline::getMax_X()
{

	double max_X = 0;

	for (unsigned i = 0; i < size; ++i)
	{
		if (point[i].getX() > max_X)
			max_X = point[i].getX();
	}

	return max_X + colours.getStrokeWidth();

}

const double Polyline::getMax_Y()
{

	double max_Y = 0;

	for (unsigned i = 0; i < size; ++i)
	{
		if (point[i].getY() > max_Y)
			max_Y = point[i].getY();
	}

	return max_Y + colours.getStrokeWidth();
}


const double Polyline::getMin_X()
{
	double min_X = getMax_X();

	for (unsigned i = 0; i < size; ++i)
	{
		if (point[i].getX() < min_X)
			min_X = point[i].getX();
	}

	return min_X;


}

const double Polyline::getMin_Y()
{

	double min_Y = getMax_Y();

	for (unsigned i = 0; i < size; ++i)
	{
		if (point[i].getX() < min_Y)
			min_Y = point[i].getX();
	}

	return min_Y;

}


void Polyline::copy(const Polyline& rhs)
{

	Figure::operator=(rhs);

	size = rhs.size;

	point = new (std::nothrow) Point[size];

	if (point)
	{
		for (unsigned i = 0; i < size; ++i)
			point[i] = rhs.point[i];
	}

}


void Polyline::clear()
{
	delete [] point;
}


bool Polyline::resize(unsigned size)
{

	clear();

	this->size = size;

	point = new (std::nothrow) Point[size];

	if (!point)
	{
		std::cout << "Maximum points for polyline reached\n";
		return false;
	}


	return true;

}
