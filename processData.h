#ifndef _PROCESSDATA_HEADER_INCLUDED_
#define _PROCESSDATA_HEADER_INCLUDED_


#include "parser.h"


class ProcessData
{

	friend std::ostream& operator << (std::ostream& os, const ProcessData& data);
	
public:

	ProcessData();
	ProcessData(const ProcessData& rhs);
	ProcessData& operator= (const ProcessData& rhs);
	~ProcessData();


	void print();
	void create(const Parse& info);
	void erase(char * needle);
	void translate(const char * description);
	void within(char * description);
	void close();


	void setFigures(const char * SVGdata);
	const double calculateAreaX() const;
	const double calculateAreaY() const;


private:
	void clear();
	void resize();
	void copy(const ProcessData& rhs);


private:

	unsigned curr;
	Figure  ** figure;

};


#endif //_PROCESSDATA_HEADER_INCLUDED_