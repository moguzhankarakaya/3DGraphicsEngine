#pragma once
#define GL
#define TEXTURED
//#define FLATSHADING
//#define WIREFRAME

#if defined(GL)
	#include "OLCConsoleWindowInterfaceGL.h"
	typedef olcConsoleGameEngineGLOOP olcConsoleGameEngineOOP;
#elif defined(GENERIC)
	#include "OLCConsoleWindowInterface.h"
#endif

#include <algorithm>

#include "Mesh.h"
#include "Camera.h"
#include "Projection.h"

class ConsoleEngine : public olcConsoleGameEngineOOP
{
public:
	ConsoleEngine();
	ConsoleEngine(std::wstring windowTitle);
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTine) override;

private:
	void clearDepthBuffer();

private:
	float                   nearPlanePos;
	float                   farPlanePos;
	float*                  depthBuffer;
	olcSprite*              texture;
	PPG::Mesh               meshedGeo;
	PPG::Camera             fpsCamera;
	PPG::Math::mat4x4		projMatrix;
	std::vector<PPG::Plane> ssClipPlanes;
	std::vector<PPG::Plane> nfClipPlanes;
};