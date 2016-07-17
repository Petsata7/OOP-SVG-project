#include "Read_writeFile.h"
#include "processData.h"

#include <string.h>

using std::nothrow;
using std::cout;
using std::ofstream;
using std::ifstream;


Read_Write::Read_Write()
{
	init();
}

Read_Write::Read_Write(const Read_Write& rhs)
{
	copy(rhs);
}

Read_Write& Read_Write::operator= (const Read_Write& rhs)
{
	if (this == &rhs)
		return *this;

	clear();
	copy(rhs);

	return *this;

}

Read_Write::~Read_Write()
{
	clear();
}



void Read_Write::splitData(char* wholeData)
{

	Parse file;
	char * testPtr = NULL;

	if (testPtr = file.getBeforeSVG(wholeData))
		beforeSVG = testPtr;


	if (testPtr = file.getSVGdata(wholeData))
		SVGdata = testPtr;

		
}

bool Read_Write::readFile(std::ifstream& ifs)
{

	ifs.seekg(0, ifs.end);
	int len = (int)ifs.tellg();
	ifs.seekg(0, ifs.beg);
	
	if (len < 0)
		return false;

	char * temp = new (nothrow) char[len + 1]; 

	if (!temp)
		return false;


	ifs.read(temp, len);
	temp[len] = '\0';


	splitData(temp);
	
	delete[] temp;

	return true;

}



bool Read_Write::open(const char* name)
{

	ifstream file(name, std::ios::binary);
	
	if (!file)
	{
		std::cerr << "Problem opening " << name << " \n";
		ofstream emptyFile(name, std::ios::binary);

		if (!emptyFile)
			cout << "Try saving at another file\n";
		else
			cout << "Try to open it now\n";

		emptyFile.close();

		return false;
	}

	clear(); //in case of opening another file, delete the information for the previous
	init();

	if (readFile(file))
		std::cout << "Successfully opened " << name << "\n";

	if (name)
	{
		
		this->fileName = new (nothrow) char[strlen(name) + 1];

		if (!fileName)
			std::cout << "you cannot 'save' at this file\n";
		else
			strcpy_s(fileName, strlen(name) + 1, name);

		
	}

	file.close();

	return true;
}

void Read_Write::close()
{
	if (fileName && fileName[0] != '\0')
		cout << "Successfully closed file " << fileName << '\n';

	clear();
	init();
}


void Read_Write::save(const ProcessData& data)
{
	saveAs(fileName, data);
}


void Read_Write::saveAs(const char* name, const ProcessData& data)
{

	std::ofstream file(name, std::ios::trunc);

	if (!file)
	{
		std::cerr << "Problem saving as " << name << " \n";
		return;
	}

	

	file
		<< beforeSVG
		<< "<svg width=\""			<< data.calculateAreaX()
		<< "\" height=\""			<< data.calculateAreaY()
		<< "\"\r\n xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\r\n\r\n"
		<< data;
	

	
	file.close();


	if (strcmp(name, fileName) == 0 )
		cout << "Successfully saved " << name << '\n';

	else
		cout << "Successfully saved as " << name << '\n';

}

void Read_Write::clear()
{
	delete[] fileName;
	delete[] beforeSVG;
	delete[] SVGdata;

}


void Read_Write::init()
{

	fileName = new (nothrow) char[1];
	if (fileName)
		fileName[0] = '\0';


	const char * defaultBeforeSVG = { "<?xml version = \"1.0\" standalone = \"no\"?> \r\n "
		"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \r\n "
		"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"> \r\n\r\n" };


	beforeSVG = new (nothrow) char[strlen(defaultBeforeSVG) + 1];
	if (beforeSVG)
		strcpy_s(beforeSVG, strlen(defaultBeforeSVG) + 1, defaultBeforeSVG);


	SVGdata = new (nothrow) char[1];
	if (SVGdata)
		SVGdata[0] = '\0';


}

void Read_Write::copy(const Read_Write& rhs)
{

	int size;

	if (rhs.fileName)
	{
		size = strlen(rhs.fileName) + 1;

		this->fileName = new (nothrow) char[size];

		if (fileName)
			strcpy_s(fileName, size, rhs.beforeSVG);
	}

	if (rhs.beforeSVG)
	{
		size = strlen(rhs.beforeSVG) + 1;

		this->beforeSVG = new (nothrow) char[size];

		if (beforeSVG)
			strcpy_s(beforeSVG, size, rhs.beforeSVG);
	}

	

	if (rhs.SVGdata)
	{
		size = strlen(rhs.SVGdata) + 1;

		this->SVGdata = new (nothrow) char[size];

		if (SVGdata)
			strcpy_s(SVGdata, size, rhs.SVGdata);
	}



}
