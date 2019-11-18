#include "..\include\GeoPrimatives.h"

PPG::Math::vec3 PPG::Triangle::Interpolate(float alpha1, float alpha2, float alpha3)
{
	Math::vec3 result;
	result.x = alpha1 * v[0].x + alpha1 * v[1].x + alpha1 * v[2].x;
	result.y = alpha1 * v[0].y + alpha1 * v[1].y + alpha1 * v[2].y;
	result.z = alpha1 * v[0].z + alpha1 * v[1].z + alpha1 * v[2].z;

	return result;
}
