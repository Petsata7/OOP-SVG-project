#include "parser.h"

#include <string.h>
#include <math.h>
#include <iostream>

using std::nothrow;
using std::cout;

Parse::Parse()	
	: colour()
{
	init();
}

Parse::Parse(const Parse& rhs)
{	
	copy(rhs);
}

Parse& Parse::operator = (const Parse& rhs)
{
	if (this == &rhs)
		return *this;

	copy(rhs);

	return *this;

}


void Parse::parseSpecificFigure(char * description)
{

	char * token = NULL;
	char * nextToken = NULL;

	if (description == NULL)
		return;

	token = strtok_s(description, " ", &nextToken);

	if (token)
		colour.setFill(token);

	token = strtok_s(NULL, " ", &nextToken);

	if (token)
		colour.setStroke(token);
		
	token = strtok_s(NULL, " ", &nextToken);

	if (token)
		colour.setStrokeWidth(atoi(token));
		

	good = true;
	unsigned t = 0;

	while (token && t < 128)
	{
		token = strtok_s(NULL, " ", &nextToken);

		if (token)
			coord[t++] = atof(token);
	}

	coordSize = t;



}

void Parse::parseUserInput(char* description)
{
	init();

	if (description == NULL)
		return;

	char * token = NULL;
	char * nextToken = NULL;
	

	token = strtok_s(description, " ", &nextToken);

	if (token == NULL)
		return;

	if (strcmp(token, "rectangle") == 0)
	{
		type = FigureType::rect;
		coordSize = 4;
	}

	else if (strcmp(token, "circle") == 0)
	{
		type = FigureType::circle;
		coordSize = 3;
	}

	else if (strcmp(token, "ellipse") == 0)
	{
		type = FigureType::ellipse;
		coordSize = 4;
	}

	else if (strcmp(token, "line") == 0)
	{
		type = FigureType::line;
		coordSize = 4;
	}

	else if (strcmp(token, "polyline") == 0)
	{
		type = FigureType::polyline;
		parseSpecificFigure(nextToken);
		return;
	}

	else if (strcmp(token, "polygon") == 0)
	{
		type = FigureType::polygon;
		parseSpecificFigure(nextToken); 
		return;
	}

	else
		return;

		

	

	good = true;

	unsigned t = 0;

	while (token && t < coordSize)
	{
		token = strtok_s(NULL, " ", &nextToken);

		if (token)
			coord[t++] = atof(token);
	}


	token = strtok_s(NULL, " ", &nextToken);


	if (token != NULL && type == FigureType::line)
	{
		colour.setStroke(token);
	}

	else
	{
				
		if (token)
			colour.setFill(token);

		token = strtok_s(NULL, " ", &nextToken);

		if (token)
			colour.setStroke(token);

				
	}

	token = strtok_s(NULL, " ", &nextToken);

	if (token)
		colour.setStrokeWidth(atoi(token));

		

}


Parse::~Parse()
{
	
}


double Parse::extractNumFromQuotes(const char * description)
{

	if (description == NULL)
		return 0;


	int qcnt = 0;
	char num[64];

	int i = 0;
	bool canBegin = false;

	while (*description && qcnt < 2 && i < 63)
	{

		if (canBegin && *description <= '9' && *description >= '0')
			num[i++] = *description;

		else if (*description == '.')
			num[i++] = *description;

		else if (*description == '"')
		{
			canBegin = true;
			qcnt++;
		}

		else if (canBegin)
			break;

	

		description++;
	}

	num[i] = '\0';

	return atof(num);

}


void Parse::parseColoursFromFile(const char * description)
{
	
	if (description == NULL)
		return;

	const char * ptr = NULL;
	char fill[64];
	char stroke[64];


	ptr = strstr(description, "fill");

	if (ptr != NULL)
	{

		int qcnt = 0;
		int i = 0;
		bool canBegin = false;


		while (*ptr && qcnt < 2 && i < 63)
		{
			if (*ptr == '"')
			{
				canBegin = true;
				qcnt++;
			}
			else if (canBegin && *ptr != '"')
				fill[i++] = *ptr;

			ptr++;
		}

		fill[i] = '\0';

		colour.setFill(fill);
	}



	ptr = strstr(description, "stroke");

	if (ptr != NULL)
	{

		int qcnt = 0;
		int i = 0;
		bool canBegin = false;


		while (*ptr && qcnt < 2 && i < 63)
		{
			if (*ptr == '"')
			{
				canBegin = true;
				qcnt++;
			}
			else if (canBegin && *ptr != '"')
				stroke[i++] = *ptr;

			ptr++;
		}

		stroke[i] = '\0';

		colour.setStroke(stroke);
	}


	ptr = strstr(description, "stroke-width");

	if (ptr != NULL)
	{
		colour.setStrokeWidth( (int)extractNumFromQuotes(ptr) );
	}


}

void Parse::extractPoints(const char* description)
{

	if (description == NULL)
		return;


	
	char num[64];
	int i = 0, k = 0;
	bool canBegin = false;


	while (*description)
	{

		if (*description == '"')
			canBegin = true;
	
		

		bool start = false;

		while (*description && canBegin && i < 128)
		{

			if (*description <= '9' && *description >= '0')
			{
				start = true;
				num[k++] = *description;
			}

			else if (start && *description == '.')
				num[k++] = *description;

			else if (start && !(*description <= '9' && *description >= '0'))
			{
				start = false;
				num[k] = '\0';
				coord[i++] = atof(num);
				k = 0;
			}

			description++;
		}

		description++;
	}

	coordSize = i;



}

void Parse::parseSVGdataFromFile(const char* description)
{

	if (description == NULL)
		return;

	const char * ptr = NULL;

	if (strstr(description, "rect") != NULL)
	{

		type = FigureType::rect;
		ptr = strstr(description, "x");
		coord[0] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "y");
		coord[1] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "width");
		coord[2] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "height");
		coord[3] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "rx");
		coord[4] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "ry");
		coord[5] = extractNumFromQuotes(ptr);

		coordSize = 6;

	}

	else if (strstr(description, "circle") != NULL)
	{

		type = FigureType::circle;
		ptr = strstr(description, "cx");
		coord[0] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "cy");
		coord[1] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "r=");
		coord[2] = extractNumFromQuotes(ptr);

		coordSize = 3;
	}

	else if (strstr(description, "polyline") != NULL)
	{
		type = FigureType::polyline;
		ptr = strstr(description, "points");
		extractPoints(ptr);

	}

	else if (strstr(description, "polygon") != NULL)
	{
		type = FigureType::polygon;
		ptr = strstr(description, "points"); //tuk
		extractPoints(ptr);

	}

	else if (strstr(description, "line") != NULL)
	{
		type = FigureType::line;
		ptr = strstr(description, "x1");
		coord[0] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "y1");
		coord[1] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "x2");
		coord[2] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "y2");
		coord[3] = extractNumFromQuotes(ptr);

		coordSize = 4;
	}

	else if (strstr(description, "ellipse") != NULL)
	{
		type = FigureType::ellipse;
		ptr = strstr(description, "cx");
		coord[0] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "cy");
		coord[1] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "rx");
		coord[2] = extractNumFromQuotes(ptr);
		ptr = strstr(description, "ry");
		coord[3] = extractNumFromQuotes(ptr);

		coordSize = 4;
	}

	

	else
		return;


	good = true;

	parseColoursFromFile(description);

	fromFile = true;

}

char *	Parse::getBeforeSVG(char * wholeData)
{


	int k = 0;
	char * ptr = NULL;

	if (wholeData != NULL)
		ptr = strstr(wholeData, "<svg");

	if (!ptr)
		return NULL;

	char * beforeSVG = new (nothrow) char[ptr - wholeData + 1];

	if (!beforeSVG)
		return NULL;

	while (*wholeData && wholeData < ptr)
	{
		beforeSVG[k] = *wholeData;
		wholeData++;
		k++;
	}

	beforeSVG[k] = '\0';

	return beforeSVG;

}


char *	Parse::getSVGdata(char * wholeData)
{

	int k = 0;
	char * start = NULL;
	char * end = NULL;

	if (wholeData == NULL)
		return NULL;

	start = strstr(wholeData, "<svg");

	if (start)
		end = strstr(start, "</svg>");

	if (!end)
		return NULL;


	
	char * SVGdata = new (nothrow) char[end - start + 7];

	if (!SVGdata)
		return NULL;

	
	while (*start && start < end + 6)
	{
		SVGdata[k++] = *start;
		start++;
	}

	SVGdata[k] = '\0';

	return SVGdata;
}


double Parse::extractHorAndVer(const char * description)
{
	if (description == NULL)
		return 0;

	int cnt = 0;
	char num[64];

	int i = 0;
	bool canBegin = false;

	while (*description && cnt < 2 && i < 63)
	{
		if (canBegin && *description <= '9' && *description >= '0')
			num[i++] = *description;
		else if (canBegin && (*description == '.' || *description == ',' || *description =='-'))
			num[i++] = *description;
		else if (*description == '=')
		{
			canBegin = true;
			cnt++;
		}
		else if (canBegin && *description == ' ')
			cnt++;

		description++;
	}

	num[i] = '\0';

	return atof(num);

}



int	Parse::extractID(const char* description)
{
	if (description == NULL)
		return -1;

	int cnt = 0;
	char ID[64];

	int i = 0;
	bool canBegin = false;

	while ( *description && cnt < 2 && i < 63 )
	{
		
		if ( canBegin && *description <= '9' && *description >= '0' )
			ID[i++] = *description;

		else if ( canBegin && (*description > '9' || *description < '0') )
			break;

		else if ( *description == '(' )
		{
			canBegin = true;
			cnt++;
		}
		else if ( canBegin && *description == ')' )
			cnt++;

		description++;
	}

	if (!canBegin)
		return -1;

	ID[i] = '\0';

	return atoi(ID);


}


void Parse::parseTranslation(const char* description)
{
	if (description == NULL)
		return;

	const char * ptr;

	translID = extractID(description);

	ptr = strstr(description, "horizontal");
	coord[0] = extractHorAndVer(ptr);

	ptr = strstr(description, "vertical");
	coord[1] = extractHorAndVer(ptr);

}


void Parse::copy(const Parse& rhs)
{
	type = rhs.type;
	colour.operator= (rhs.colour);
	fromFile = rhs.fromFile;
	good = rhs.good;
	translID = rhs.translID;

	for (int i = 0; i < 12; ++i)
		coord[i] = rhs.coord[i];

}

void Parse::init()
{
	fromFile = false;
	good = false;
	type = FigureType::none;	
	translID = -1;

	coordSize = 0;

	for (int i = 0; i < 128; ++i)
		coord[i] = 0.0;
}
