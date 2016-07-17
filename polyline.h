#ifndef _POLYLINE_HEADER_INCLUDED_
#define _POLYLINE_HEADER_INCLUDED_

#include "figure.h"
#include "point.h"

class Polyline : public Figure
{

public:

	Polyline();
	Polyline(const Polyline& rhs);
	Polyline& operator = (const Polyline& rhs);
	~Polyline();


	Figure* clone() const { return new (std::nothrow) Polyline(*this); }

	void print();
	void setCoord(const double * coord, unsigned size);
	void setColours(const Colours_Manager& colours);
	void translate(const Point& tr);
	bool within(FigureType type, const double * coordinates, unsigned size);


	const double getMax_Y();
	const double getMax_X();


protected:

	void writeToStream(std::ostream& os) const;

private:

	bool resize(unsigned size);
	void copy(const Polyline& rhs);
	void clear();
	const double getMin_Y();
	const double getMin_X();

private:

	Point * point;
	unsigned size;


};


#endif //_POLYLINE_HEADER_INCLUDED_