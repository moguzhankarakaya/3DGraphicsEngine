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
	/*
	testCube.mesh = std::vector<PPG::Triangle>{
		// SOUTH
		{ {0.0f, 0.0f,  0.0f},     {0.0f, 1.0f,  0.0f},     {1.0f, 1.0f,  0.0f} },
		{ {0.0f, 0.0f,  0.0f},     {1.0f, 1.0f,  0.0f},     {1.0f, 0.0f,  0.0f} },
		// EAST
		{ {1.0f, 0.0f,  0.0f},     {1.0f, 1.0f,  0.0f},     {1.0f, 1.0f, -1.0f} },
		{ {1.0f, 0.0f,  0.0f},     {1.0f, 1.0f, -1.0f},     {1.0f, 0.0f, -1.0f} },
		// NORTH
		{ {1.0f, 0.0f, -1.0f},     {1.0f, 1.0f, -1.0f},     {0.0f, 1.0f, -1.0f} },
		{ {1.0f, 0.0f, -1.0f},     {0.0f, 1.0f, -1.0f},     {0.0f, 0.0f, -1.0f} },
		// WEST
		{ {0.0f, 0.0f, -1.0f},     {0.0f, 1.0f, -1.0f},     {0.0f, 1.0f,  0.0f} },
		{ {0.0f, 0.0f, -1.0f},     {0.0f, 1.0f,  0.0f},     {0.0f, 0.0f,  0.0f} },
		// TOP
		{ {0.0f, 1.0f,  0.0f},     {0.0f, 1.0f, -1.0f},     {1.0f, 1.0f, -1.0f} },
		{ {0.0f, 1.0f,  0.0f},     {1.0f, 1.0f, -1.0f},     {1.0f, 1.0f,  0.0f} },
		// BOTTOM
		{ {1.0f, 0.0f, -1.0f},     {0.0f, 0.0f, -1.0f},     {0.0f, 0.0f,  0.0f} },
		{ {1.0f, 0.0f, -1.0f},     {0.0f, 0.0f,  0.0f},     {1.0f, 0.0f,  0.0f} },
	};
	*/
	testCube.LoadObjectFile(L"assets/Tea_Pot.obj");
	projMatrix = PPG::Projection((float)ScreenWidth() / (float)ScreenHeight(), 90.0f, 0.1f, 1000.0f).GetPerspectiveProjection();
	fTheta     = 0;

	return true;
}

bool ConsoleEngine::OnUserUpdate(float fElapsedTime)
{
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
	
	PPG::Math::mat4x4 translation;
	PPG::Math::mat4x4 rotation;
	PPG::Math::mat4x4 modelView;

	fTheta += 16.0f * fElapsedTime;
	if (fTheta > 360.0f) fTheta -= 360.0f;
	translation.translate(PPG::Math::vec3(0.0f, 2.0f, -8.0f));
	//rotation.rotate(fTheta *  1.0f, 0);
	//rotation.rotate(fTheta *  2.0f, 2);
	rotation.rotate(205.0f, 0);
	rotation.rotate(-25.0f, 1);
	rotation.rotate( 10.0f, 2);
	//rotation.rotate(fTheta * 5.0f, 1);


	modelView = translation * rotation;

	// Preparing Drawing Buffer (Lack of Depth Buffer in Console Rendering Engine)
	// Implemention of the "Painter's Algorithm"
	std::vector<PPG::Triangle> trianglesToRaster;
	for (auto& triangle : testCube.mesh)
	{
		PPG::Triangle projTri, worldTri;

		// Transform triangles (primatives) into world space
		worldTri.v[0] = (modelView * triangle.v[0].homogenize(1.0f)).cartesian();
		worldTri.v[1] = (modelView * triangle.v[1].homogenize(1.0f)).cartesian();
		worldTri.v[2] = (modelView * triangle.v[2].homogenize(1.0f)).cartesian();

		// Culling Routine of Triangle Primatives
		PPG::Math::vec3 normal = (worldTri.v[1] - worldTri.v[0]).cross(worldTri.v[2] - worldTri.v[0]);
		normal.normalize();

		if (normal.anglebetween(PPG::Math::vec3(worldTri.v[0] - cameraPos)) < 90.0f)
		{
			// Illumination (Shading)
			PPG::Math::vec3 lightDir(1.0f, 1.0f, -1.0f);
			lightDir.normalize();
			float luminacity = normal * lightDir;
			CHAR_INFO color = GetColour(luminacity);
			worldTri.color = color.Attributes;
			worldTri.symbol = color.Char.UnicodeChar;

			// Apply perspective projection to the triangles (transformation into pixel space / canonical view volume)
			projTri.v[0] = (projMatrix * worldTri.v[0].homogenize(1.0f)).cartesian();
			projTri.v[1] = (projMatrix * worldTri.v[1].homogenize(1.0f)).cartesian();
			projTri.v[2] = (projMatrix * worldTri.v[2].homogenize(1.0f)).cartesian();
			projTri.color = worldTri.color;
			projTri.symbol = worldTri.symbol;

			// Scale pixels into view target size
			projTri.v[0].x = (projTri.v[0].x + 1.0f) * 0.5f * (float)ScreenWidth();
			projTri.v[0].y = (projTri.v[0].y + 1.0f) * 0.5f * (float)ScreenHeight();
			projTri.v[1].x = (projTri.v[1].x + 1.0f) * 0.5f * (float)ScreenWidth();
			projTri.v[1].y = (projTri.v[1].y + 1.0f) * 0.5f * (float)ScreenHeight();
			projTri.v[2].x = (projTri.v[2].x + 1.0f) * 0.5f * (float)ScreenWidth();
			projTri.v[2].y = (projTri.v[2].y + 1.0f) * 0.5f * (float)ScreenHeight();

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
		// Fragment drawing (Pixel Rasterization)
		FillTriangle(tri.v[0].x, tri.v[0].y,
			tri.v[1].x, tri.v[1].y,
			tri.v[2].x, tri.v[2].y,
			tri.symbol, tri.color);
			
		#ifdef WIREFRAME
			DrawTriangle(tri.v[0].x, tri.v[0].y,
				tri.v[1].x, tri.v[1].y,
				tri.v[2].x, tri.v[2].y,
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