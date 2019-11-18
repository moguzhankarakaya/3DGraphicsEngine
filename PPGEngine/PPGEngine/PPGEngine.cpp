#include <iostream>

#include "ConsoleEngine.h"
#include "Projection.h"


int main()
{
	ConsoleEngine window;
	if(window.ConstructConsole(256,252,4,4))
	{ 
		window.Start();
	}
	return 0;
}