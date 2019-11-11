#include "..\include\ConsoleEngine.h"

ConsoleEngine::ConsoleEngine()
{
	m_sAppName = L"Demo Window";
}

ConsoleEngine::ConsoleEngine(std::wstring windowTitle)
{
	m_sAppName = windowTitle;
}

bool ConsoleEngine::OnUserCreate()
{	
	testCube.mesh = 
	{
		// SOUTH
		{0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f},
		// EAST
		{1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f, 1.0f},
		// NORTH
		{1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1.0f},
		// WEST
		{0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f, 0.0f},
		// TOP
		{0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 0.0f},
		// BOTTOM
		{1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 0.0f},
	};

	return true;
}

bool ConsoleEngine::OnUserUpdate(float fElapsedTine)
{
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

	// Draw routine
	for (auto triange : testCube.mesh)
	{

	}

	return true;
}
    