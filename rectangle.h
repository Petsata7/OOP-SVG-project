#ifndef _RECTANGLE_HEADER_INCLUDED_
#define _RECTANGLE_HEADER_INCLUDED_

#include "figure.h"
#include "circle.h"


class Rectangle : public Figure
{

public:

	Rectangle();
	Rectangle(const Rectangle& rhs);
	Rectangle& operator = (const Rectangle& rhs);
	~Rectangle();

	Figure* clone() const { return new (std::nothrow) Rectangle(*this); }


	void print();
	void translate(const Point& tr);
	void setCoord(const double * coord, unsigned size);
	void setColours(const Colours_Manager& colours);
	bool within(FigureType type, const double * coordinates, unsigned size);


	const double getWidth()	const	{ return width;		}
	const double getHeight()const	{ return height;	}
	const double getX()		const	{ return p.getX();	}
	const double getY()		const	{ return p.getY();	}
	const double getMax_Y();
	const double getMax_X();

protected:

	void writeToStream(std::ostream& os) const;
	
private:
	double max(double a, double b);

private:

	Point	p; // x and y
	double	width;
	double	height;
	double	rx;
	double	ry;

};



#endif //_RECTANGLE_HEADER_INCLUDED_