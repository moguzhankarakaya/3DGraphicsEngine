#include <iostream>

#include "ConsoleEngine.h"
#include "Projection.h"


int main()
{
	ConsoleEngine window;
	if(window.ConstructConsole(256*2, 252*2, 2, 2))
	{ 
		window.Start();
	}
	return 0;
}