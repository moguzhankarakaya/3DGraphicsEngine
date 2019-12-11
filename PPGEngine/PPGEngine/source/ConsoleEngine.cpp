#include "ConsoleEngine.h"

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
	meshedGeo.LoadObjectFile(L"assets/Models/Cube.obj");
	texture		 = new olcSprite(L"assets/Textures/Wall_0.spr");
	nearPlanePos = 0.01f; farPlanePos = 1000.0f;
	depthBuffer  = new float[ScreenWidth() * ScreenHeight()];

	projMatrix   = PPG::Projection((float)ScreenWidth() / (float)ScreenHeight(), 90.0f, nearPlanePos, farPlanePos).GetPerspectiveProjection();
	fpsCamera    = PPG::Camera(PPG::Math::vec3(0.0f, 0.0f, 0.0f), PPG::Math::vec3(0.0f, 1.0f, 0.0f), 0.5f, 5.0f);

	ssClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{ -1.0f,  0.0f,  0.0f, 0.0f }, PPG::Math::vec4{  1.0f,  0.0f,  0.0f, 1.0f} });
	ssClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{  1.0f,  0.0f,  0.0f, 0.0f }, PPG::Math::vec4{ -1.0f,  0.0f,  0.0f, 1.0f} });
	ssClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{  0.0f, -1.0f,  0.0f, 0.0f }, PPG::Math::vec4{  0.0f,  1.0f,  0.0f, 1.0f} });
	ssClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{  0.0f,  1.0f,  0.0f, 0.0f }, PPG::Math::vec4{  0.0f, -1.0f,  0.0f, 1.0f} });
	nfClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{0.0f, 0.0f,  1.0f, 0.0f}, PPG::Math::vec4{0.0f, 0.0f, nearPlanePos, 1.0f} });
	nfClipPlanes.push_back(PPG::Plane{ PPG::Math::vec4{0.0f, 0.0f, -1.0f, 0.0f}, PPG::Math::vec4{0.0f, 0.0f,  farPlanePos, 1.0f} });

	return true;
}

bool ConsoleEngine::OnUserUpdate(float fElapsedTime)
{
	if (GetKey(VK_SPACE).bHeld)
		fpsCamera.ResetCamera();
	if (GetKey(L'W').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getForwardDir() * fElapsedTime);
	if (GetKey(L'S').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getForwardDir() * -1.0f * fElapsedTime);
	if (GetKey(L'A').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getRightDir() * fElapsedTime);
	if (GetKey(L'D').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getRightDir() * -1.0f * fElapsedTime);
	if (GetKey(L'Q').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getUpDir() * fElapsedTime);
	if (GetKey(L'E').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getUpDir() * - 1.0f * fElapsedTime);
	if (GetKey(VK_UP).bHeld)
		fpsCamera.TiltCamera(1.0f * fElapsedTime);
	if (GetKey(VK_DOWN).bHeld)
		fpsCamera.TiltCamera(-1.0f * fElapsedTime);
	if (GetKey(VK_LEFT).bHeld)
		fpsCamera.PanCamera(-1.0f * fElapsedTime);
	if (GetKey(VK_RIGHT).bHeld)
		fpsCamera.PanCamera(1.0f * fElapsedTime);
	
	PPG::Math::mat4x4 translation, rotation, model, view, modelView;
	PPG::Triangle     projTri, worldTri;
	translation.translate(PPG::Math::vec3{ 0.0f, 0.0f, -5.0f });
	rotation.rotate(0.0f, 0);
	model  = (translation * rotation);
	view = fpsCamera.getViewMatrix();
	modelView =  view * model;

	// Preparing Drawing Buffer (Lack of Depth Buffer in Console Rendering Engine)
	// Implemention of the "Painter's Algorithm"
	std::vector<PPG::Triangle> trianglesToRaster;
 	for (auto& triangle : meshedGeo.mesh)
	{

		// Transform triangles (primatives) into world space
		worldTri = triangle * modelView;

		// Culling Routine of Triangle Primatives
		PPG::Math::vec4 normal{ worldTri.Normal() };

		if (normal * worldTri.ViewVector() < 0.0f)
		{
			// Illumination (Shading)
			PPG::Math::vec4 lightDir(1.0f, 1.0f, -1.0f, 0.0f);
			lightDir.normalize();
			float luminacity = max(0.1f, normal * lightDir);
			CHAR_INFO color = GetColour(luminacity);
			worldTri.color = color.Attributes;
			worldTri.symbol = color.Char.UnicodeChar;

			std::vector<PPG::Triangle> clippedWorldTri{ worldTri.ClipAgainst(nfClipPlanes) };

			for (auto& tri : clippedWorldTri)
			{
				// Apply perspective projection to the triangles (transformation into pixel space / canonical view volume)
				projTri = tri * projMatrix;
				
				std::vector<PPG::Triangle> clippedProjectedTri{ projTri.ClipAgainst(ssClipPlanes) };
				
				trianglesToRaster.insert(trianglesToRaster.end(), clippedProjectedTri.begin(), clippedProjectedTri.end());
			}
		}
	}
	
	// Clear screen before calling drawing routines
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

	#ifndef TEXTURED
		// Sort triangles from back to front
		std::sort(trianglesToRaster.begin(), 
				  trianglesToRaster.end(), 
			[](PPG::Triangle& t1, PPG::Triangle& t2)
			{
				float depth1 = t1.Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f).z;
				float depth2 = t2.Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f).z;
				return depth1 > depth2;
			});
	#else
		clearDepthBuffer();
	#endif

	for (auto& tri : trianglesToRaster)
	{
		// Scale pixels into view target size
		PPG::Math::vec3 v1{ (tri.v[0].cartesian() + PPG::Math::vec3{ 1.0f, 1.0f, 0.0f }).outer(PPG::Math::vec3{ 0.5f*(float)ScreenWidth() - 0.1f, 0.5f*(float)ScreenHeight() - 0.1f, 1.0f }) };
		PPG::Math::vec3 v2{ (tri.v[1].cartesian() + PPG::Math::vec3{ 1.0f, 1.0f, 0.0f }).outer(PPG::Math::vec3{ 0.5f*(float)ScreenWidth() - 0.1f, 0.5f*(float)ScreenHeight() - 0.1f, 1.0f }) };
		PPG::Math::vec3 v3{ (tri.v[2].cartesian() + PPG::Math::vec3{ 1.0f, 1.0f, 0.0f }).outer(PPG::Math::vec3{ 0.5f*(float)ScreenWidth() - 0.1f, 0.5f*(float)ScreenHeight() - 0.1f, 1.0f }) };

		// Fragment drawing (Pixel Rasterization)
		#ifdef TEXTURED
			TexturedTriangle((int)v1.x, (int)v1.y, tri.t[0].u, tri.t[0].v, tri.t[0].w,
							 (int)v2.x, (int)v2.y, tri.t[1].u, tri.t[1].v, tri.t[1].w,
							 (int)v3.x, (int)v3.y, tri.t[2].u, tri.t[2].v, tri.t[2].w,
							 depthBuffer, texture);
		#else
			#ifdef FLATSHADING
				FillTriangle((int)v1.x, (int)v1.y,
							 (int)v2.x, (int)v2.y,
							 (int)v3.x, (int)v3.y,
							 tri.symbol, tri.color);
			#else
				FillTriangle((int)v1.x, (int)v1.y,
							 (int)v2.x, (int)v2.y,
							 (int)v3.x, (int)v3.y,
							 PIXEL_SOLID, FG_WHITE);
			#endif
		#endif
		#ifdef WIREFRAME
			DrawTriangle((int)v1.x, (int)v1.y,
						 (int)v2.x, (int)v2.y,
						 (int)v3.x, (int)v3.y,
						 PIXEL_SOLID, FG_WHITE);
		#endif
	}

	return true;
}
    
void ConsoleEngine::clearDepthBuffer()
{
	for (size_t i = 0; i < ScreenHeight()*ScreenWidth(); i++)
	{
		depthBuffer[i] = 0.0f;
	}
}
