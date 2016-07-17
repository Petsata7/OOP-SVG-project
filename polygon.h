#ifndef _POLYGON_HEADER_INCLUDED_
#define _POLYGON_HEADER_INCLUDED_

#include "figure.h"


class Polygon : public Figure
{

public:

	Polygon();
	Polygon(const Polygon& rhs);
	Polygon& operator = (const Polygon& rhs);
	~Polygon();


	Figure* clone() const { return new (std::nothrow) Polygon(*this); }

	void print();
	void setCoord(const double * coord, unsigned size);
	void setColours(const Colours_Manager& colours);
	void translate(const Point& tr);
	bool within(FigureType type, const double * coordinates, unsigned size);


	const double	getMax_Y();
	const double	getMax_X();


protected:

	void writeToStream(std::ostream& os) const;

private:

	bool resize(unsigned size);
	void copy(const Polygon& rhs);
	void clear();
	const double getMin_Y();
	const double getMin_X();

private:

	Point * point;
	unsigned size;
	


};


#endif //_POLYGON_HEADER_INCLUDED_