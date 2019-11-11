#include <iostream>

#include "ConsoleEngine.h"

int main()
{
	ConsoleEngine window;

	if(window.ConstructConsole(256,240,4,4))
	{ 
		window.Start();
	}
	return 0;
}