#ifndef _COLOURS_MANAGER_HEADER_INCLUDED_
#define _COLOURS_MANAGER_HEADER_INCLUDED_



class Colours_Manager
{

public:
	Colours_Manager();
	Colours_Manager(const Colours_Manager& rhs);
	Colours_Manager& operator=(const Colours_Manager& rhs);
	~Colours_Manager();

	void setFill		(const char * fill);
	void setStroke		(const char * stroke);
	void setStrokeWidth(const int width);

	const char	*	getFill()			const	{ return fill;		   }
	const char	*	getStroke()			const	{ return stroke;	   }
	const int		getStrokeWidth()	const	{ return stroke_width; }


private:

	char fill[64];
	char stroke[64];
	int	 stroke_width;

};


#endif //_COLOURS_MANAGER_HEADER_INCLUDED_