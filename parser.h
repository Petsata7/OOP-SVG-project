#ifndef _PARSER_HEADER_INCLUDED_
#define _PARSER_HEADER_INCLUDED_

#include "figure.h"
#include "colours_manager.h"

class Parse
{

public:

	Parse();
	Parse(const Parse& rhs);
	Parse& operator= (const Parse& rhs);
	~Parse();

	void	parseUserInput			(char * description);
	void	parseSVGdataFromFile	(const char* description);
	void	parseTranslation		(const char* description);
	char *	getBeforeSVG			(char * description);
	char *	getSVGdata				(char * description);

	
	const double*	getCoord()		const	{ return coord;		}
	const double	getHor()		const	{ return coord[0];	}
	const double	getVer()		const	{ return coord[1];	}
	bool			isFromFile()	const	{ return fromFile;	}
	bool			isGood()		const	{ return good;		}
	FigureType		getType()		const	{ return type;		}
	const int		getID()			const	{ return translID;  }
	const unsigned	getCoordSize()	const	{ return coordSize; }
	Colours_Manager getColours()	const	{ return colour;	}


private:

	void	parseSpecificFigure(char * description);
	void	init();
	void	copy( const Parse& rhs);
	void	parseColoursFromFile(const char * description);
	void	extractPoints(const char* description);
	int		extractID(const char* description);
	double	extractNumFromQuotes(const char * description);
	double	extractHorAndVer(const char * description);
	
	
private:
		
	bool		fromFile;
	bool		good;
	double		coord[128];	
	int			translID;
	unsigned	coordSize;
	FigureType	type;
	Colours_Manager colour;
	
};

#endif //_PARSER_HEADER_INCLUDED_