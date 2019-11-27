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
	testCube.LoadObjectFile(L"assets/Debugging_Axis.obj");
	/*
	testCube.mesh = std::vector< PPG::Triangle>{

		//// SOUTH
		{ {0.0f, 0.0f, 0.0f},    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },

		//// EAST                                                      
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 0.0f, 1.0f} },

		//// NORTH                                                     
		{ {1.0f, 0.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 1.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 0.0f, 1.0f} },

		//// WEST                                                      
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 0.0f} },
		{ {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 0.0f},    {0.0f, 0.0f, 0.0f} },

		//// TOP                                                       
		{ {0.0f, 1.0f, 0.0f},    {0.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} },
		{ {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 0.0f} },

		//// BOTTOM                                                    
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f} },
		{ {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
	};
	*/
	projMatrix = PPG::Projection((float)ScreenWidth() / (float)ScreenHeight(), 90.0f, 0.1f, 1000.0f).GetPerspectiveProjection();
	fpsCamera  = PPG::Camera(PPG::Math::vec3(0.0f, 0.0f, 0.0f), PPG::Math::vec3(0.0f, 1.0f, 0.0f), 5.0f, 20.0f);
	fTheta     = 0;

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
		fpsCamera.MoveCamera(fpsCamera.getWorldUpDir() * fElapsedTime);
	if (GetKey(L'E').bHeld)
		fpsCamera.MoveCamera(fpsCamera.getWorldUpDir() * - 1.0f * fElapsedTime);
	if (GetKey(VK_UP).bHeld)
		fpsCamera.TiltCamera(1.0f * fElapsedTime);
	if (GetKey(VK_DOWN).bHeld)
		fpsCamera.TiltCamera(-1.0f * fElapsedTime);
	if (GetKey(VK_LEFT).bHeld)
		fpsCamera.PanCamera(1.0f * fElapsedTime);
	if (GetKey(VK_RIGHT).bHeld)
		fpsCamera.PanCamera(-1.0f * fElapsedTime);

	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
	
	PPG::Math::mat4x4 translation, rotation, model, view, modelView;

	translation.translate(PPG::Math::vec3(0.0f, 0.0f, -18.0f));	
	//rotation.rotate(90.0f, 0);
	//rotation.rotate(180.0f, 1);
	//rotation.rotate( 90.0f, 2);
	model  = (translation * rotation);
	view = fpsCamera.getViewMatrix();
	modelView =  view * model;

	// Preparing Drawing Buffer (Lack of Depth Buffer in Console Rendering Engine)
	// Implemention of the "Painter's Algorithm"
	std::vector<PPG::Triangle> trianglesToRaster;
	for (auto& triangle : testCube.mesh)
	{
		PPG::Triangle projTri, worldTri;

		// Transform triangles (primatives) into world space
		worldTri = triangle * modelView;

		// Culling Routine of Triangle Primatives
		PPG::Math::vec3 normal = worldTri.Normal();

		if (normal.anglebetween(worldTri.ViewVector(fpsCamera.getCameraPos())) < 90.0f)
		{
			// Illumination (Shading)
			PPG::Math::vec3 lightDir(0.0f, -1.0f, -1.0f);
			lightDir.normalize();
			float luminacity = normal * lightDir;
			CHAR_INFO color = GetColour(luminacity);
			worldTri.color = color.Attributes;
			worldTri.symbol = color.Char.UnicodeChar;

			// Apply perspective projection to the triangles (transformation into pixel space / canonical view volume)
			projTri = worldTri * projMatrix;
			projTri.color  = worldTri.color;
			projTri.symbol = worldTri.symbol;
				
			trianglesToRaster.push_back(projTri);
		}
	}
	
	// Sort triangles from back to front
	std::sort(trianglesToRaster.begin(), 
			  trianglesToRaster.end(), 
		[](PPG::Triangle& t1, PPG::Triangle& t2)
		{
			float depth1 = t1.Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f).z;
			float depth2 = t2.Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f).z;
			return depth1 > depth2;
		});

	for (auto& tri : trianglesToRaster)
	{
		// Scale pixels into view target size
		PPG::Triangle2D tri2D = tri.ImageCordinates((float)ScreenWidth(), (float)ScreenHeight());

		// Fragment drawing (Pixel Rasterization)
		FillTriangle((int)tri2D.v[0].x, (int)tri2D.v[0].y,
			(int)tri2D.v[1].x, (int)tri2D.v[1].y,
			(int)tri2D.v[2].x, (int)tri2D.v[2].y,
			//tri.symbol, tri.color);
			PIXEL_SOLID, FG_WHITE);
		#ifdef WIREFRAME
			DrawTriangle((int)tri2D.v[0].x, (int)tri2D.v[0].y,
						 (int)tri2D.v[1].x, (int)tri2D.v[1].y,
						 (int)tri2D.v[2].x, (int)tri2D.v[2].y,
				PIXEL_SOLID, FG_BLACK);
		#endif
	}

	return true;
}
    
// Taken From Javidx9's project.
CHAR_INFO ConsoleEngine::GetColour(float lum)
{
	short bg_col, fg_col;
	wchar_t sym;
	int pixel_bw = (int)(13.0f*lum);
	switch (pixel_bw)
	{
	case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

	case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
	case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
	case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
	case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

	case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
	case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
	case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
	case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

	case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
	case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
	case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
	case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
	default:
		bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
	}

	CHAR_INFO c;
	c.Attributes = bg_col | fg_col;
	c.Char.UnicodeChar = sym;
	return c;
}