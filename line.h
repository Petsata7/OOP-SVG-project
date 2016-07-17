#ifndef _LINE_HEADER_INCLUDED_
#define _LINE_HEADER_INCLUDED_

#include "figure.h"
#include "point.h"

using std::ostream;

class Line : public Figure
{

public:

	Line();
	Line(const Line& rhs);
	Line& operator = (const Line& rhs);
	~Line();

	Figure* clone() const { return new (std::nothrow) Line(*this); }


	void print();
	void setCoord(const double * coord, unsigned size);
	void setColours(const Colours_Manager& colours);
	void translate(const Point& tr);
	bool within(FigureType type, const double * coordinates, unsigned size);


	const double getMax_Y();
	const double getMax_X();

protected:

	void writeToStream(std::ostream& os) const ;
	
private:

	double max(double a, double b);
	double min(double a, double b);

private:
	Point p1;
	Point p2;

};

#endif //_LINE_HEADER_INCLUDED_