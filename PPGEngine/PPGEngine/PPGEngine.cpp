#include <iostream>

#include "ConsoleEngine.h"

void printVector(const PPG::vec3& vectorToPrint)
{
	std::cout << "Vector : x = " << vectorToPrint.x << "\ty = " << vectorToPrint.y << "\tz = " << vectorToPrint.z << std::endl;
	std::cout << "\n";
}

void printTriangle(PPG::Triangle& tri)
{
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << "Triangle vertex " << i << "\t";
		printVector(tri.v[i]);
	}
	std::cout << "\n";
}

int main()
{
	ConsoleEngine window;

	PPG::vec3 vector1 = { 2.0f, 1.5f, 1.0f };
	printVector(vector1);
	PPG::vec3 vector2 = { 3.0f, 4.0f, 6.0f };
	printVector(vector2);
	PPG::vec3 vector3 = vector1 * vector2;
	printVector(vector3);
	PPG::vec3 vector4 = vector3;
	printVector(vector4);

	/*
	if(window.ConstructConsole(256,240,4,4))
	{ 
		window.Start();
	}
	*/
	return 0;
}