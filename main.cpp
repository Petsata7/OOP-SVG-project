#include "commands.h"
#include "read_writeFile.h"
#include "processData.h"


int main()
{


	/****************************************************************************************/
	/*   Input patterns:																	*/
	/*			                                                                            */
	/*      > command arguments                                                             */
	/*                                                                                      */
	/*		for polyline: polyline fill stroke stroke-width coordinates(even-amount)		*/
	/*      for polygon: polygon fill stroke stroke-width coordinates(even-amount)			*/
	/*      for line: line x1 y1 x2 y2 stroke stroke-width									*/
	/*      For all other figures: type respective coordinates fill stroke stroke-width		*/
	/*																						*/
	/*		> translate (index) horizontal= vertical=										*/
	/*																						*/
	/****************************************************************************************/



	Read_Write file;
	ProcessData data;
	Command command;

	command.startProgramme(file, data);


	return 0;
}