#pragma once
#define GENERIC
//#define WIREFRAME

#if defined(GL)
	#include "OLCConsoleWindowInterfaceGL.h"
typedef olcConsoleGameEngineGLOOP olcConsoleGameEngineOOP;
#elif defined(GENERIC)
	#include "OLCConsoleWindowInterface.h"
#endif

#include <algorithm>

#include "Mesh.h"
#include "Projection.h"

class ConsoleEngine : public olcConsoleGameEngineOOP
{
public:
	ConsoleEngine();
	ConsoleEngine(std::wstring windowTitle);
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTine) override;

private:
	CHAR_INFO GetColour(float lum);

private:
	float             fTheta;
	PPG::Mesh         testCube;
	PPG::Math::vec3   cameraPos;
	PPG::Math::mat4x4 projMatrix;
};