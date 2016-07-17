#ifndef _Figure_HEADER_INCLUDED_
#define _Figure_HEADER_INCLUDED_

#include "point.h"
#include "colours_manager.h"

enum FigureType
{
	none,
	rect,
	circle,
	line,
	ellipse,
	polyline,
	polygon
};


class Figure
{

	friend std::ostream& operator<< (std::ostream& os, const Figure& fig);

public:

	Figure();
	Figure(const Figure& rhs);
	Figure& operator = (const Figure& rhs);
	virtual ~Figure();


	static	Figure * createFigure(FigureType type);
	virtual Figure * clone() const = 0;


	virtual void setCoord(const double * info, unsigned size) = 0; //size?
	virtual void setColours(const Colours_Manager& colours ) = 0;
	virtual void print() = 0;
	virtual void translate(const Point& p) = 0;
	virtual bool within(FigureType type, const double * coordinates, unsigned size) = 0;


	const char *			getName() const;
	FigureType				getType() const { return type; }
	virtual const double	getMax_Y() = 0;
	virtual const double	getMax_X() = 0;


protected:

	virtual void writeToStream( std::ostream& whereto ) const = 0;	
	void setType(FigureType type);

	Point getTopLeft()	const { return TL; }
	Point getBtmRight() const { return BR; }

	void setBtmRight(const Point&);
	void setTopLeft(const Point&);

private:

	void swapIfNeeded();




protected:

	Colours_Manager colours;

private:

	Point TL; //bounding rectangle
	Point BR;
	FigureType type;

};




#endif //_Figure_HEADER_INCLUDED_