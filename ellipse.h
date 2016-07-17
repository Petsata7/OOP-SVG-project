#ifndef _ELLIPSE_HEADER_INCLUDED_
#define _ELLIPSE_HEADER_INCLUDED_

#include "circle.h"


class Ellipse : public Circle
{

public:
	Ellipse();
	Ellipse(const Ellipse& rhs);
	Ellipse& operator = (const Ellipse & rhs);
	~Ellipse();


	Figure* clone() const { return new (std::nothrow) Ellipse(*this); }

	void print();
	void setCoord(const double * coord, unsigned size);
	void translate(const Point& tr);
	bool within(FigureType type, const double * coordinates, unsigned size);


	
	const double getRY()	const { return ry; }
	const double getMax_Y();

protected:

	void writeToStream(std::ostream& os) const;


private:

	double ry; //rx is radius from Circle

};


#endif //_ELLIPSE_HEADER_INCLUDED_