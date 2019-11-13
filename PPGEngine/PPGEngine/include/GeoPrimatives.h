#pragma once
#include "PPGMath.h"

namespace PPG
{
	struct Triangle
	{
		vec3 v[3];

		Triangle(vec3 v1 = vec3(), PPG::vec3 v2 = vec3(), PPG::vec3 v3 = vec3()) : v{ v1, v2, v3 } {} 

	};
}