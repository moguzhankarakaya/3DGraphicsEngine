#pragma once
#include "PPGMath.h"

namespace PPG
{
	struct Triangle
	{
		Math::vec3 v[3];
		short      color;
		wchar_t    symbol;

		Triangle(Math::vec3 v1 = Math::vec3(), Math::vec3 v2 = Math::vec3(), Math::vec3 v3 = Math::vec3()) : v{ v1, v2, v3 } {} 

		Math::vec3 Interpolate(float alpha1, float alpha2, float alpha3);

	};
}