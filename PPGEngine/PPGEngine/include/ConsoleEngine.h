#pragma once
#define GENERIC

#if defined(GL)
	#include "OLCConsoleWindowInterfaceGL.h"
#elif defined(GENERIC)
	#include "OLCConsoleWindowInterface.h"
#endif

#include "Mesh.h"

class ConsoleEngine : public olcConsoleGameEngine
{
public:
	ConsoleEngine();

	ConsoleEngine(std::wstring windowTitle);

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTine) override;

private:
	Mesh testCube;

};