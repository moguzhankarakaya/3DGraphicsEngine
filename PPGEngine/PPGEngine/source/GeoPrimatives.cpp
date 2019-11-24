#include "GeoPrimatives.h"

PPG::Triangle& PPG::Triangle::operator=(const Triangle & rhs)
{
	v[0]   = rhs.v[0];
	v[1]   = rhs.v[1];
	v[2]   = rhs.v[2];
	color  = rhs.color;
	symbol = rhs.symbol;

	return *this;
}

PPG::Triangle PPG::Triangle::operator*(const Math::mat4x4 transform)
{
	Triangle result;
	result.v[0] = (transform * v[0].homogenize(1.0f)).cartesian();
	result.v[1] = (transform * v[1].homogenize(1.0f)).cartesian();
	result.v[2] = (transform * v[2].homogenize(1.0f)).cartesian();

	return result;
}

PPG::Math::vec3 PPG::Triangle::Normal()
{
	Math::vec3 result;
	result = (v[1] - v[0]).cross(v[2] - v[0]);
	result.normalize();

	return result;
}

PPG::Math::vec3 PPG::Triangle::Interpolate(float alpha1, float alpha2, float alpha3)
{
	Math::vec3 result{ alpha1 * v[0].x + alpha1 * v[1].x + alpha1 * v[2].x ,
					   alpha1 * v[0].y + alpha1 * v[1].y + alpha1 * v[2].y ,
					   alpha1 * v[0].z + alpha1 * v[1].z + alpha1 * v[2].z
					 };

	return result;
}

PPG::Math::vec3 PPG::Triangle::ViewVector(const Math::vec3 & viewpoint)
{
	Math::vec3 result{ this->Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f) - viewpoint };

	return result;
}

PPG::Math::vec3 PPG::Triangle::Reflect(const Math::vec3 & incoming)
{
	Math::vec3 result{ incoming + this->Normal() * ((incoming * -1.0f)* this->Normal()) * 2.0f };
	
	return result;
}

PPG::Triangle2D PPG::Triangle::ImageCordinates(const float screenWidth, const float screenHeight)
{
	Triangle2D result{ {(v[0].x + 1.0f) * 0.5f * screenWidth, (v[0].y + 1.0f) * 0.5f * screenHeight} ,
					   {(v[1].x + 1.0f) * 0.5f * screenWidth, (v[1].y + 1.0f) * 0.5f * screenHeight} ,
					   {(v[2].x + 1.0f) * 0.5f * screenWidth, (v[2].y + 1.0f) * 0.5f * screenHeight} };
	
	return result;
}
