#ifndef _COMMANDS_HEADER_INCLUDED_
#define _COMMANDS_HEADER_INCLUDED_

#include "Read_WriteFile.h"
#include "ProcessData.h"

class Command 
{
public:

	Command();
	Command(const Command& rhs);
	Command& operator = (const Command& rhs);
	~Command();

	void startProgramme(Read_Write& file, ProcessData& data);

private:

	char command[128];
	char line[1024];
	
};

#endif //_COMMANDS_HEADER_INCLUDED_