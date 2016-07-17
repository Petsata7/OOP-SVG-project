#include "commands.h"
#include "parser.h"

#include <iostream>
#include <string.h>

using std::cin;

Command::Command()	
{
	command[0] = '\0';
	line[0] = '\0';
}

Command::Command(const Command& rhs)	
{
	strcpy_s(command, 128 ,rhs.command);
	strcpy_s(line, 1024 ,rhs.line);
}

Command& Command::operator = (const Command& rhs)
{
	if (this == &rhs)
		return *this;

	strcpy_s(command, 128 , rhs.command);
	strcpy_s(line, 1024, rhs.line);

	return *this;
}

Command::~Command()
{

}

void Command::startProgramme(Read_Write& file, ProcessData& data)
{

	bool canStart = false;
	char c; //use to read > and space


	while (strcmp(command, "exit") != 0)
	{
		line[0] = '\0';
		cin >> c >> command;
		cin.get(c);
		if (c != '\n')
			cin.getline(line, 1024, '\n');


		if (strcmp(command, "open") == 0)
		{
			canStart = file.open(line);
			data.setFigures(file.getSVGdata());
		}


		if (canStart)
		{

			if (strcmp(command, "close") == 0)
			{
				file.close();
				data.close();
			}

			else if (strcmp(command, "save") == 0)
				file.save(data);

			else if (strcmp(command, "saveas") == 0)
				file.saveAs(line, data);

			else if (strcmp(command, "print") == 0)
				data.print();

			else if (strcmp(command, "create") == 0)
			{
				Parse figure;
				figure.parseUserInput(line);
				data.create(figure);
			}

			else if (strcmp(command, "erase") == 0)
				data.erase(line);

			else if (strcmp(command, "translate") == 0)
				data.translate(line);

			else if (strcmp(command, "within") == 0)
				data.within(line);
		}
		
	}


	file.close();
	data.close();

}

