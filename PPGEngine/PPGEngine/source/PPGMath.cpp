#include "PPGMath.h"

PPG::vec3& PPG::vec3::operator=(const vec3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

PPG::vec3 PPG::vec3::operator*(const vec3& rhs) const
{
	vec3 result;
	result.x = this->x * rhs.x;
	result.y = this->y * rhs.y;
	result.z = this->z * rhs.z;

	return result;
}

PPG::vec3 PPG::vec3::operator*(float scalar) const
{
	vec3 result;
	result.x = this->x*scalar;
	result.y = this->y*scalar;
	result.z = this->z*scalar;

	return result;
}

PPG::vec3 PPG::vec3::operator+(const vec3& rhs) const
{
	vec3 result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;

	return result;
}

PPG::vec3 PPG::vec3::operator+(float scalar) const
{
	vec3 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;
	result.z = this->z + scalar;

	return result;
}

PPG::vec3 PPG::vec3::operator-(const vec3 & rhs) const
{
	vec3 result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;

	return result;
}

PPG::vec3 PPG::vec3::operator-(float scalar) const
{
	vec3 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	result.z = this->z - scalar;

	return result;
}

PPG::vec3 PPG::vec3::operator/(float scalar) const
{
	vec3 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	result.z = this->z / scalar;

	return result;
}

PPG::vec3 PPG::vec3::cross(const vec3& rhs)
{
	vec3 result;
	result.x = y * rhs.z - z * rhs.y;
	result.y = z * rhs.x - x * rhs.z;
	result.z = x * rhs.y - y * rhs.x;
	return result;
}

void PPG::vec3::norm()
{
	float magnitude = std::sqrt(x*x + y * y + z * z);
	x /= magnitude; y /= magnitude; z /= magnitude;
}

PPG::vec4& PPG::vec4::operator=(const vec4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return *this;
}

PPG::vec4 PPG::vec4::operator*(const vec4& rhs) const
{
	vec4 result;
	result.x = this->x * rhs.x;
	result.y = this->y * rhs.y;
	result.z = this->z * rhs.z;
	result.w = this->w * rhs.w;

	return result;
}

PPG::vec4 PPG::vec4::operator*(float scalar) const
{
	vec4 result;
	result.x = this->x*scalar;
	result.y = this->y*scalar;
	result.z = this->z*scalar;
	result.w = this->w*scalar;

	return result;
}

PPG::vec4 PPG::vec4::operator+(const vec4& rhs) const
{
	vec4 result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;
	result.w = this->w + rhs.w;

	return result;
}

PPG::vec4 PPG::vec4::operator+(float scalar) const
{
	vec4 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;
	result.z = this->z + scalar;
	result.w = this->w + scalar;

	return result;
}

PPG::vec4 PPG::vec4::operator-(const vec4 & rhs) const
{
	vec4 result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;
	result.w = this->w - rhs.w;

	return result;
}

PPG::vec4 PPG::vec4::operator-(float scalar) const
{
	vec4 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	result.z = this->z - scalar;
	result.w = this->w - scalar;

	return result;
}

void PPG::vec4::norm()
{
	float magnitude = std::sqrt(x*x + y * y + z * z + w * w);
	x /= magnitude; y /= magnitude; z /= magnitude; w /= magnitude;
}

PPG::mat3x3 & PPG::mat3x3::operator=(const mat3x3 & rhs)
{
	a11 = rhs.a11; a12 = rhs.a12; a13 = rhs.a13;
	a21 = rhs.a21; a22 = rhs.a22; a23 = rhs.a23;
	a31 = rhs.a31; a32 = rhs.a32; a33 = rhs.a33;
	
	return *this;
}

PPG::vec3 PPG::mat3x3::operator*(const vec3 & rhs) const
{
	vec3 result;
	result.x = a11 * rhs.x + a12 * rhs.y + a13 * rhs.z;
	result.y = a21 * rhs.x + a22 * rhs.y + a23 * rhs.z;
	result.z = a31 * rhs.x + a32 * rhs.y + a33 * rhs.z;
	
	return result;
}

PPG::mat3x3 PPG::mat3x3::operator*(float scalar) const
{
	mat3x3 result;
	result.a11 *= scalar; result.a12 *= scalar; result.a13 *= scalar;
	result.a21 *= scalar; result.a22 *= scalar; result.a23 *= scalar;
	result.a31 *= scalar; result.a32 *= scalar; result.a33 *= scalar;

	return result;
}

PPG::vec3 PPG::mat3x3::operator[](int idx) const
{
	vec3 result;
	if (idx == 1)
	{
		result.x = a11; result.y = a12; result.z = a13;
	}
	else if (idx == 2)
	{
		result.x = a21; result.y = a22; result.z = a23;
	}
	else
	{
		result.x = a31; result.y = a32; result.z = a33;
	}
	return result;
}

void PPG::mat3x3::rotate(float angle, int axis)
{
	
}

PPG::mat4x4 & PPG::mat4x4::operator=(const mat4x4 & rhs)
{
	// TODO: insert return statement here
}

PPG::vec4 PPG::mat4x4::operator*(const vec4 & rhs) const
{
	return vec4();
}

PPG::mat4x4 PPG::mat4x4::operator*(float scalar) const
{
	return mat4x4();
}

PPG::vec4 PPG::mat4x4::operator[](int idx) const
{
	return vec4();
}

void PPG::mat4x4::rotate(float angle, int axis)
{
}

void PPG::mat4x4::translate(vec3 distance)
{
}
