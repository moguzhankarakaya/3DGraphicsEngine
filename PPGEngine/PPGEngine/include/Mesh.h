#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <strstream>

#include "GeoPrimatives.h"

namespace PPG
{
	struct Mesh
	{
		std::vector<Triangle> mesh;

		bool LoadObjectFile(std::wstring pathToFile);
	};
}