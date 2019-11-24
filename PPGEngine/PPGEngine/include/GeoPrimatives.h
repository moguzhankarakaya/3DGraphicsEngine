#pragma once
#include "PPGMath.h"

namespace PPG
{
	struct Triangle;
	struct Triangle2D;

	struct Triangle
	{
		Math::vec3 v[3];
		short      color;
		wchar_t    symbol;

		Triangle(Math::vec3 v1 = Math::vec3(), Math::vec3 v2 = Math::vec3(), Math::vec3 v3 = Math::vec3()) : v{ v1, v2, v3 } {} 
		
		Triangle&   operator=(const Triangle& rhs);
		Triangle    operator*(const Math::mat4x4 transform);
		Math::vec3  Normal();
		Math::vec3  Interpolate(float alpha1, float alpha2, float alpha3);
		Math::vec3  ViewVector(const Math::vec3& viewpoint);
		Math::vec3  Reflect(const Math::vec3& incoming);
		Triangle2D  ImageCordinates(const float screenWidth, const float screenHeight);
	};
	
	struct Triangle2D
	{
		Math::vec2 v[3];
		short      color;
		wchar_t    symbol;

		Triangle2D(Math::vec2 v1 = Math::vec2(), Math::vec2 v2 = Math::vec2(), Math::vec2 v3 = Math::vec2()) : v{ v1, v2, v3 } {}
	};
}