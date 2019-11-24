#include "PPGMath.h"

PPG::Math::vec2 & PPG::Math::vec2::operator=(const vec2 & rhs)
{
	x = rhs.x;
	y = rhs.y;

	return *this;
}

float PPG::Math::vec2::operator*(const vec2 & rhs) const
{
	float result = 0;
	result += this->x * rhs.x;
	result += this->y * rhs.y;

	return result;
}

PPG::Math::vec2 PPG::Math::vec2::operator*(const float scalar) const
{
	vec2 result;
	result.x = this->x*scalar;
	result.y = this->y*scalar;

	return result;
}

PPG::Math::vec2 PPG::Math::vec2::operator+(const vec2 & rhs) const
{
	vec2 result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;

	return result;
}


PPG::Math::vec2 PPG::Math::vec2::operator+(const float scalar) const
{
	vec2 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;

	return result;
}

PPG::Math::vec2 PPG::Math::vec2::operator-(const vec2 & rhs) const
{
	vec2 result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;

	return result;
}

PPG::Math::vec2 PPG::Math::vec2::operator-(const float scalar) const
{
	vec2 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;

	return result;
}

PPG::Math::vec2 PPG::Math::vec2::operator/(const float scalar) const
{
	vec2 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;

	return result;
}

float PPG::Math::vec2::operator[](int idx) const
{
	if (idx == 0)
	{
		return x;
	}
	else if (idx == 1)
	{
		return y;
	}
}

float PPG::Math::vec2::magnitude() const
{
	return sqrt(x * x + y * y);
}

float PPG::Math::vec2::anglebetween(const vec2 & rhs) const
{
	float product = (*this) * rhs;
	float angle = acosf(product / (this->magnitude() * rhs.magnitude()));
	return Conversions::RadToDegree(angle);
}

void PPG::Math::vec2::normalize()
{
	float magnitude = std::sqrt(x*x + y * y);
	if (magnitude != 0.0f)
	{
		x /= magnitude; y /= magnitude;
	}
}
 

PPG::Math::vec3& PPG::Math::vec3::operator=(const vec3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

float PPG::Math::vec3::operator*(const vec3& rhs) const
{
	float result = 0;
	result += this->x * rhs.x;
	result += this->y * rhs.y;
	result += this->z * rhs.z;

	return result;
}

PPG::Math::vec3 PPG::Math::vec3::operator*(const float scalar) const
{
	vec3 result;
	result.x = this->x*scalar;
	result.y = this->y*scalar;
	result.z = this->z*scalar;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}

PPG::Math::vec3 PPG::Math::vec3::operator+(const vec3& rhs) const
{
	vec3 result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator+=(const vec3 & rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;

	return *this;
}

PPG::Math::vec3 PPG::Math::vec3::operator+(const float scalar) const
{
	vec3 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;
	result.z = this->z + scalar;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator+=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;

	return *this;
}

PPG::Math::vec3 PPG::Math::vec3::operator-(const vec3 & rhs) const
{
	vec3 result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator-=(const vec3 & rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;

	return *this;
}

PPG::Math::vec3 PPG::Math::vec3::operator-(const float scalar) const
{
	vec3 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	result.z = this->z - scalar;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator-=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;

	return *this;
}

PPG::Math::vec3 PPG::Math::vec3::operator/(const float scalar) const
{
	vec3 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	result.z = this->z / scalar;

	return result;
}

PPG::Math::vec3& PPG::Math::vec3::operator/=(const float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;

	return *this;
}

float PPG::Math::vec3::operator[](int idx) const
{
	if (idx == 0)
	{
		return x;
	}
	else if (idx == 1)
	{
		return y;
	}
	else if (idx == 2)
	{
		return z;
	}
}

PPG::Math::vec3 PPG::Math::vec3::cross(const vec3& rhs) const
{
	vec3 result;
	result.x = y * rhs.z - z * rhs.y;
	result.y = z * rhs.x - x * rhs.z;
	result.z = x * rhs.y - y * rhs.x;
	return result;
}

PPG::Math::vec3 PPG::Math::vec3::outer(const vec3 & rhs) const
{
	vec3 result;
	result.x = x * rhs.x;
	result.y = y * rhs.y;
	result.z = z * rhs.z;

	return result;
}

void PPG::Math::vec3::normalize()
{
	float magnitude = std::sqrt(x*x + y * y + z * z);
	if (magnitude != 0.0f)
	{
		x /= magnitude; y /= magnitude; z /= magnitude;
	}
}

float PPG::Math::vec3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float PPG::Math::vec3::anglebetween(const vec3 & rhs) const
{
	float product = (*this) * rhs;
	float angle = acosf( product / ( this->magnitude() * rhs.magnitude() ) );
	return Conversions::RadToDegree(angle);
}

PPG::Math::vec4 PPG::Math::vec3::homogenize(const float w) const
{
	vec4 result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}

PPG::Math::vec4& PPG::Math::vec4::operator=(const vec4& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return *this;
}

float PPG::Math::vec4::operator*(const vec4& rhs) const
{
	float result = 0;
	result += this->x * rhs.x;
	result += this->y * rhs.y;
	result += this->z * rhs.z;
	result += this->w * rhs.w;

	return result;
}

PPG::Math::vec4 PPG::Math::vec4::operator*(const float scalar) const
{
	vec4 result;
	result.x = this->x*scalar;
	result.y = this->y*scalar;
	result.z = this->z*scalar;
	result.w = this->w*scalar;

	return result;
}

PPG::Math::vec4& PPG::Math::vec4::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;

	return *this;
}

PPG::Math::vec4 PPG::Math::vec4::operator+(const vec4& rhs) const
{
	vec4 result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;
	result.w = this->w + rhs.w;

	return result;
}

PPG::Math::vec4& PPG::Math::vec4::operator+=(const vec4 & rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	this->w += rhs.w;

	return *this;
}

PPG::Math::vec4 PPG::Math::vec4::operator+(const float scalar) const
{
	vec4 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;
	result.z = this->z + scalar;
	result.w = this->w + scalar;

	return result;
}

PPG::Math::vec4& PPG::Math::vec4::operator+=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	this->w += scalar;

	return *this;
}

PPG::Math::vec4 PPG::Math::vec4::operator-(const vec4 & rhs) const
{
	vec4 result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;
	result.w = this->w - rhs.w;

	return result;
}

PPG::Math::vec4& PPG::Math::vec4::operator-=(const vec4 & rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	this->w -= rhs.w;

	return *this;
}

PPG::Math::vec4 PPG::Math::vec4::operator-(const float scalar) const
{
	vec4 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	result.z = this->z - scalar;
	result.w = this->w - scalar;

	return result;
}

PPG::Math::vec4 & PPG::Math::vec4::operator-=(const float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	this->w -= scalar;

	return *this;
}

PPG::Math::vec4 PPG::Math::vec4::operator/(const float scalar) const
{
	vec4 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	result.z = this->z / scalar;
	result.w = this->w / scalar;

	return result;
}

PPG::Math::vec4 & PPG::Math::vec4::operator/=(const float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	this->w /= scalar;

	return *this;
}

float PPG::Math::vec4::operator[](int idx) const
{
	if (idx == 0)
	{
		return x;
	}
	else if (idx == 1)
	{
		return y;
	}
	else if (idx == 2)
	{
		return z;
	}
	else if (idx == 3)
	{
		return w;
	}
}

PPG::Math::vec4 PPG::Math::vec4::outer(const vec4 & rhs) const
{
	vec4 result;
	result.x = x * rhs.x;
	result.y = y * rhs.y;
	result.z = z * rhs.z;
	result.w = w * rhs.w;

	return result;
}

void PPG::Math::vec4::normalize()
{
	float magnitude = std::sqrt(x*x + y * y + z * z + w * w);
	if (magnitude != 0.0f)
	{
		x /= magnitude; y /= magnitude; z /= magnitude; w /= magnitude;
	}
}

void PPG::Math::vec4::homogenize()
{
	if (w != 0.0f)
	{
		x /= w; y /= w; z /= w;
	}
}

PPG::Math::vec3 PPG::Math::vec4::cartesian()
{
	vec3 result;
	homogenize();
	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

PPG::Math::mat3x3 & PPG::Math::mat3x3::operator=(const mat3x3 & rhs)
{
	a11 = rhs.a11; a12 = rhs.a12; a13 = rhs.a13;
	a21 = rhs.a21; a22 = rhs.a22; a23 = rhs.a23;
	a31 = rhs.a31; a32 = rhs.a32; a33 = rhs.a33;
	
	return *this;
}

PPG::Math::vec3 PPG::Math::mat3x3::operator*(const vec3 & rhs) const
{
	vec3 result;
	result.x = a11 * rhs.x + a12 * rhs.y + a13 * rhs.z;
	result.y = a21 * rhs.x + a22 * rhs.y + a23 * rhs.z;
	result.z = a31 * rhs.x + a32 * rhs.y + a33 * rhs.z;
	
	return result;
}

PPG::Math::mat3x3 PPG::Math::mat3x3::operator*(const float scalar) const
{
	mat3x3 result;
	result.a11 *= scalar; result.a12 *= scalar; result.a13 *= scalar;
	result.a21 *= scalar; result.a22 *= scalar; result.a23 *= scalar;
	result.a31 *= scalar; result.a32 *= scalar; result.a33 *= scalar;

	return result;
}

PPG::Math::mat3x3 PPG::Math::mat3x3::operator*(const mat3x3 & rhs) const
{
	mat3x3 result;
	result.a11 = a11 * rhs.a11 + a12 * rhs.a21 + a13 * rhs.a31;
	result.a12 = a11 * rhs.a12 + a12 * rhs.a22 + a13 * rhs.a32;
	result.a13 = a11 * rhs.a13 + a12 * rhs.a23 + a13 * rhs.a33;

	result.a21 = a21 * rhs.a11 + a22 * rhs.a21 + a23 * rhs.a31;
	result.a22 = a21 * rhs.a12 + a22 * rhs.a22 + a23 * rhs.a32;
	result.a23 = a21 * rhs.a13 + a22 * rhs.a23 + a23 * rhs.a33;

	result.a31 = a31 * rhs.a11 + a32 * rhs.a21 + a33 * rhs.a31;
	result.a32 = a31 * rhs.a12 + a32 * rhs.a22 + a33 * rhs.a32;
	result.a33 = a31 * rhs.a13 + a32 * rhs.a23 + a33 * rhs.a33;
	
	return result;
}

PPG::Math::vec3 PPG::Math::mat3x3::operator[](const int idx) const
{
	vec3 result;
	if (idx == 0)
	{
		result.x = a11; result.y = a12; result.z = a13;
	}
	else if (idx == 1)
	{
		result.x = a21; result.y = a22; result.z = a23;
	}
	else if (idx == 2)
	{
		result.x = a31; result.y = a32; result.z = a33;
	}

	return result;
}

void PPG::Math::mat3x3::rotate(const float angle, int axis)
{
	float  angleRadian =  angle * PI / 180.0f;
	mat3x3 rotation;
	if (axis == 0)
	{
		rotation.a22 = cos(angleRadian); rotation.a23 = -1 * sin(angleRadian);
		rotation.a32 = sin(angleRadian); rotation.a33 = cos(angleRadian);
		(*this) = rotation * (*this);
	}
	else if (axis == 1)
	{
		rotation.a11 = cos(angleRadian); rotation.a13 = -1 * sin(angleRadian);
		rotation.a31 = sin(angleRadian); rotation.a33 = cos(angleRadian);
		(*this) = rotation * (*this);
	}
	else if (axis == 2)
	{
		rotation.a11 = cos(angleRadian); rotation.a12 = -1 * sin(angleRadian);
		rotation.a21 = sin(angleRadian); rotation.a22 = cos(angleRadian);
		(*this) = rotation * (*this);
	}
}

PPG::Math::mat4x4 & PPG::Math::mat4x4::operator=(const mat4x4 & rhs)
{
	a11 = rhs.a11; a12 = rhs.a12; a13 = rhs.a13; a14 = rhs.a14;
	a21 = rhs.a21; a22 = rhs.a22; a23 = rhs.a23; a24 = rhs.a24;
	a31 = rhs.a31; a32 = rhs.a32; a33 = rhs.a33; a34 = rhs.a34;
	a41 = rhs.a41; a42 = rhs.a42; a43 = rhs.a43; a44 = rhs.a44;

	return *this;
}

PPG::Math::vec4 PPG::Math::mat4x4::operator*(const vec4 & rhs) const
{
	vec4 result;
	result.x = a11 * rhs.x + a12 * rhs.y + a13 * rhs.z + a14 * rhs.w;
	result.y = a21 * rhs.x + a22 * rhs.y + a23 * rhs.z + a24 * rhs.w;
	result.z = a31 * rhs.x + a32 * rhs.y + a33 * rhs.z + a34 * rhs.w;
	result.w = a41 * rhs.x + a42 * rhs.y + a43 * rhs.z + a44 * rhs.w;

	return result;
}

PPG::Math::mat4x4 PPG::Math::mat4x4::operator*(const float scalar) const
{
	mat4x4 result;
	result.a11 *= scalar; result.a12 *= scalar; result.a13 *= scalar; result.a14 *= scalar;
	result.a21 *= scalar; result.a22 *= scalar; result.a23 *= scalar; result.a24 *= scalar;
	result.a31 *= scalar; result.a32 *= scalar; result.a33 *= scalar; result.a34 *= scalar;
	result.a41 *= scalar; result.a42 *= scalar; result.a43 *= scalar; result.a44 *= scalar;

	return result;
}

PPG::Math::mat4x4 PPG::Math::mat4x4::operator*(const mat4x4 & rhs) const
{
	mat4x4 result;
	result.a11 = a11 * rhs.a11 + a12 * rhs.a21 + a13 * rhs.a31 + a14 * rhs.a41;
	result.a12 = a11 * rhs.a12 + a12 * rhs.a22 + a13 * rhs.a32 + a14 * rhs.a42;
	result.a13 = a11 * rhs.a13 + a12 * rhs.a23 + a13 * rhs.a33 + a14 * rhs.a43;
	result.a14 = a11 * rhs.a14 + a12 * rhs.a24 + a13 * rhs.a34 + a14 * rhs.a44;

	result.a21 = a21 * rhs.a11 + a22 * rhs.a21 + a23 * rhs.a31 + a24 * rhs.a41;
	result.a22 = a21 * rhs.a12 + a22 * rhs.a22 + a23 * rhs.a32 + a24 * rhs.a42;
	result.a23 = a21 * rhs.a13 + a22 * rhs.a23 + a23 * rhs.a33 + a24 * rhs.a43;
	result.a24 = a11 * rhs.a14 + a12 * rhs.a24 + a13 * rhs.a34 + a24 * rhs.a44; 
	
	result.a31 = a31 * rhs.a11 + a32 * rhs.a21 + a33 * rhs.a31 + a34 * rhs.a41;
	result.a32 = a31 * rhs.a12 + a32 * rhs.a22 + a33 * rhs.a32 + a34 * rhs.a42;
	result.a33 = a31 * rhs.a13 + a32 * rhs.a23 + a33 * rhs.a33 + a34 * rhs.a43;
	result.a34 = a11 * rhs.a14 + a12 * rhs.a24 + a13 * rhs.a34 + a34 * rhs.a44;

	result.a41 = a41 * rhs.a11 + a42 * rhs.a21 + a43 * rhs.a31 + a44 * rhs.a41;
	result.a42 = a41 * rhs.a12 + a42 * rhs.a22 + a43 * rhs.a32 + a44 * rhs.a42;
	result.a43 = a41 * rhs.a13 + a42 * rhs.a23 + a43 * rhs.a33 + a44 * rhs.a43;
	result.a44 = a41 * rhs.a14 + a42 * rhs.a24 + a43 * rhs.a34 + a44 * rhs.a44;

	return result;
}

PPG::Math::vec4 PPG::Math::mat4x4::operator[](int idx) const
{
	vec4 result;
	if (idx == 0)
	{
		result.x = a11; result.y = a12; result.z = a13; result.w = a14;
	}
	else if (idx == 1)
	{
		result.x = a21; result.y = a22; result.z = a23; result.w = a24;
	}
	else if (idx == 2)
	{
		result.x = a31; result.y = a32; result.z = a33; result.w = a34;
	}
	else if (idx == 3)
	{
		result.x = a41; result.y = a42; result.z = a43; result.w = a44;
	}

	return result;
}

void PPG::Math::mat4x4::rotate(const float angle, int axis)
{
	mat3x3 currentR;
	currentR.a11 = a11; currentR.a12 = a12; currentR.a13 = a13;
	currentR.a21 = a21; currentR.a22 = a22; currentR.a23 = a23;
	currentR.a31 = a31; currentR.a32 = a32; currentR.a33 = a33;
	
	vec3 currentT;
	currentT.x = a14; currentT.y = a24; currentT.z = a34;

	mat3x3 rotation;
	rotation.rotate(angle, axis);

	mat3x3 endR = rotation * currentR;
	vec3   endT = rotation * currentT;

	a11 = endR.a11; a12 = endR.a12; a13 = endR.a13; a14 = endT.x;
	a21 = endR.a21; a22 = endR.a22; a23 = endR.a23; a24 = endT.y;
	a31 = endR.a31; a32 = endR.a32; a33 = endR.a33; a34 = endT.z;
}

void PPG::Math::mat4x4::translate(vec3 distance)
{
	a11 += distance.x * a41; a12 += distance.x * a42; a13 += distance.x * a43;
	a21 += distance.y * a41; a22 += distance.y * a42; a23 += distance.y * a43;
	a31 += distance.z * a41; a32 += distance.z * a42; a33 += distance.z * a43;

	a14 += distance.x;
	a24 += distance.y;
	a34 += distance.z;
}