#ifndef _READ_FILE_HEADER_INCLUDED_
#define _READ_FILE_HEADER_INCLUDED_


#include "processData.h"

#include <iostream>
#include <fstream>


class Read_Write 
{

public:

	Read_Write();
	Read_Write(const Read_Write& rhs);
	Read_Write& operator = (const Read_Write& rhs);
	~Read_Write();


	bool open(const char* name);  
	void close();
	void save(const ProcessData& data);
	void saveAs(const char * name, const ProcessData& data);
	

	char * getSVGdata() { return SVGdata; }

private:

	void copy(const Read_Write& rhs);
	void clear();
	void init();
	void splitData(char* wholeData);
	bool readFile(std::ifstream& ifs);
	

private:

	char *	fileName;
	char *	beforeSVG;
	char *	SVGdata;
	
};



#endif //_READ_FILE_HEADER_INCLUDED_