#include "processData.h"
#include "parser.h"
#include "rectangle.h"
#include "circle.h"
#include "line.h"

#include <iostream>
#include <string.h>

using std::ostream;
using std::cout;

ProcessData::ProcessData()
	: curr(0)
	, figure(NULL)
{
	resize();
}

ProcessData::ProcessData(const ProcessData& rhs)
{
	copy(rhs);
}

ProcessData& ProcessData::operator = (const ProcessData& rhs)
{
	
	if (this == &rhs)
		return *this;

	clear();
	copy(rhs);

	return *this;

}

ProcessData::~ProcessData()
{
	clear();
}


void ProcessData::create(const Parse& info)
{
	
	if (info.isGood())
	{
			
		if ( (figure[curr] = Figure::createFigure( info.getType())) != NULL)
		{
			figure[curr]->setCoord( info.getCoord(), info.getCoordSize() );

			figure[curr]->setColours( info.getColours() );

			if ( !info.isFromFile() )
				cout << "Successfully created a " << figure[curr]->getName() << " (" << curr + 1 << ")\n";

			curr++;
			resize();

		}
	}
	
}



void ProcessData::erase(char * needle)
{

	int ID = atoi(needle);


	if (ID > (int)curr || ID <= 0)
	{
		cout << "There is no figure number " << ID << " !\n";
		return;
	}


	cout << "Erased a " << figure[ID - 1]->getName() << " (" << ID << ")\n";

	delete figure[ID - 1];

	for (unsigned i = ID - 1; i < curr; ++i) //curr - 1
	{
		figure[i] = figure[i + 1];
	}


	curr--;
	
}


void ProcessData::translate(const char * description)
{

	Parse tr;
	tr.parseTranslation(description);

	Point P( tr.getHor(), tr.getVer() );


	if (tr.getID() != -1) 
	{
		if (tr.getID() <= (int)curr)
		{
			figure[tr.getID() - 1]->translate(P);

			cout << "Translated " << '(' << tr.getID() << ")\n";
		}

		else
			cout << "Wrong ID\n";
	}

	else
	{

		for (unsigned i = 0; i < curr; ++i)
		{
			figure[i]->translate( P );
		}

		cout << "Translated all figures\n";

	}


}


void ProcessData::within(char * description)
{

	char copy[1024];

	if (description != NULL)
		strcpy_s(copy, 1024, description);


	Parse info;
	info.parseUserInput(description);
	
	if ( !info.isGood() )
		return;
	

	bool flag = false;

	for (unsigned i = 0; i < curr; ++i)
	{
		if ( figure[i]->within(info.getType(), info.getCoord(), info.getCoordSize() ) )
		{
			cout << '(' << i + 1 << ") ";
			figure[i]->print();
			flag = true;
		}
	}


	if (!flag)
	{
		cout << "No figures are located within " << copy << '\n';
	}

}
	

void ProcessData::close()
{
	clear();
	resize();
}



void ProcessData::setFigures(const char * SVGdata)
{

	if (SVGdata == NULL)
	{
		cout << "Data couldn't be loaded properly!\n";
		return;
	}

	
	char  currFigure[1024];
	const char * s = SVGdata; //start
	const char * e = SVGdata; //end

	

	while (s && e)
	{

		const char 
			* fig1 = s, 
			* fig2 = s, 
			* fig3 = s,
			* fig4 = s,
			* fig5 = s,
			* fig6 = s,
			* min = NULL;

		fig1 = strstr(s, "rect");
		fig2 = strstr(s, "circle");
		fig3 = strstr(s, "polyline");
		fig4 = strstr(s, "polygon"); 
		fig5 = strstr(s, "ellipse");
		fig6 = strstr(s, "line");
		
		
		if (fig1 != NULL)//getting first non null ptr
			min = fig1;

		else if (fig2 != NULL)
			min = fig2;

		else if (fig3 != NULL)
			min = fig3;

		else if (fig4 != NULL)
			min = fig4;

		else if (fig5 != NULL)
			min = fig5;

		else if (fig6 != NULL)
			min = fig6;




		if (fig2 != NULL) //getting figures in a row
		{
			if (fig2 < min)
				min = fig2;
		}

		if (fig3 != NULL)
		{
			if (fig3 < min)
				min = fig3;
		}

		if (fig4 != NULL)
		{
			if (fig4 < min)
				min = fig4;
		}
		
		if (fig5 != NULL)
		{
			if (fig5 < min)
				min = fig5;
		}

		if (fig6 != NULL)
		{
			if (fig6 < min)
				min = fig6;
		}
		


		s = min;
		e = strstr(e, "/>");

		if (s != NULL)
		{
			if (e != NULL)
			{

				int len = e - s;

				while (e && len < 0)
				{
					e++;
					e = strstr(e, "/>");
					len = e - s;
				}


				if (len < 1023)
				{
					int check = strncpy_s(currFigure, 1023, s, len);

					if (check == 0)
					{
						Parse figure;
						figure.parseSVGdataFromFile(currFigure);
						create(figure);
					}
				}

				s+= strlen(currFigure);
				e++;
			}
			else
				break;
		}
		else
			break;
		
	}

}

void ProcessData::print()
{
	for (unsigned i = 0; i < curr; ++i)
	{
		cout << ' ' << i + 1 << ". ";
		figure[i]->print();
	}

}


const double ProcessData::calculateAreaX() const
{

	double max_X = 0;

	for (unsigned i = 0; i < curr; ++i)
	{
		if (figure[i]->getMax_X() > max_X)
			max_X = figure[i]->getMax_X();
	}
	
	return max_X;
}



const double ProcessData::calculateAreaY() const
{

	double max_Y = 0;

	for (unsigned i = 0; i < curr; ++i)
	{
		if (figure[i]->getMax_Y() > max_Y)
			max_Y = figure[i]->getMax_Y();
	}

	return max_Y;

	
}

ostream& operator << (ostream& os, const ProcessData& data)
{


	for (unsigned i = 0; i < data.curr; ++i)
	{
		os << *(data.figure[i]);
	}


	os << "\r\n</svg>\r\n";

	
	return os;
}


void ProcessData::clear()
{
	unsigned size = curr + 1;

	for (unsigned i = 0; i < size; ++i)
	{
		delete figure[i];
	}

	delete[] figure;

	curr = 0;

	figure = NULL;
}

void ProcessData::resize()
{

	unsigned size = curr + 1;

	Figure ** temp = new Figure *[size];

	for (unsigned i = 0; i < curr; ++i)
		temp[i] = figure[i];

	temp[curr] = NULL; //pointer for the next figure

	delete[] figure;

	figure = temp;

}

void ProcessData::copy(const ProcessData& rhs)
{

	curr = rhs.curr;

	unsigned size = curr + 1;
	figure = new Figure *[size];

	for (unsigned i = 0; i < size - 1; i++)
		figure[i] = rhs.figure[i]->clone();


	figure[curr] = NULL;
}

