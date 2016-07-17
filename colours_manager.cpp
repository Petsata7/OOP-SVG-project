#include "colours_manager.h"

#include <string.h>



Colours_Manager::Colours_Manager()
{
	strcpy_s(fill, 64, "transparent");
	strcpy_s(stroke, 64, "none");

	stroke_width = 0;
}


Colours_Manager::Colours_Manager(const Colours_Manager& rhs)
{ 

	strcpy_s(fill, 64, rhs.fill);
	strcpy_s(stroke, 64, rhs.stroke);

	stroke_width = rhs.stroke_width;
}


Colours_Manager& Colours_Manager::operator = (const Colours_Manager& rhs)
{

	if (this == &rhs)
		return*this;


	strcpy_s(fill, 64, rhs.fill);
	strcpy_s(stroke, 64, rhs.stroke);

	stroke_width = rhs.stroke_width;

	return *this;

}

Colours_Manager::~Colours_Manager()
{


}

void Colours_Manager::setFill(const char * fill)
{
	if (fill)
		strcpy_s(this->fill, 64, fill);


}

void Colours_Manager::setStroke(const char * stroke)
{

	if (stroke)
		strcpy_s(this->stroke, 64, stroke);


}

void Colours_Manager::setStrokeWidth(const int width)
{
	if (width > 1)
		stroke_width = width;

}