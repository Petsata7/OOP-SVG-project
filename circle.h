#ifndef _CIRCLE_HEADER_INCLUDED_
#define _CIRCLE_HEADER_INCLUDED_

#include "figure.h"
#include "point.h"



class Circle : public Figure
{

public:
	Circle();
	Circle(const Circle& rhs);
	Circle& operator = (const Circle & rhs);
	~Circle();


	Figure* clone() const { return new (std::nothrow) Circle(*this); }

	void print();
	void setCoord(const double * coord, unsigned size);
	void setColours(const Colours_Manager& colours);
	void translate(const Point& tr);
	bool within(FigureType type, const double * coordinates, unsigned size);


	const double getRadius()const { return radius;		  }
	const double getX()		const { return center.getX(); }
	const double getY()		const { return center.getY(); }
	const double getMax_Y();
	const double getMax_X();


protected:

	void writeToStream(std::ostream& os) const;

protected:

	Point center;
	double radius;

};

#endif //_CIRCLE_HEADER_INCLUDED_