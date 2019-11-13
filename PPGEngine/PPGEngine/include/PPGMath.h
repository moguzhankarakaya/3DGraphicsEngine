#pragma once
#include <cmath>

namespace PPG
{

	struct vec3
	{
		float x, y, z;

		vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x{ _x }, y{ _y }, z{ _z } {}

		vec3(const vec3& _vec3) : x{_vec3.x}, y{_vec3.y}, z{_vec3.z} { }

		vec3& operator=(const vec3& rhs);
		vec3 operator*(const vec3& rhs) const;
		vec3 operator*(float scalar) const;
		vec3 operator+(const vec3& rhs) const;
		vec3 operator+(float scalar) const;
		vec3 operator-(const vec3& rhs) const;
		vec3 operator-(float scalar) const;
		vec3 operator/(float scalar) const;
		vec3 cross(const vec3& rhs);
		void norm();

	};

	struct vec4
	{
		float x, y, z, w;

		vec4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}

		vec4(const vec3& _vec3, float _w) : x{ _vec3.x }, y{ _vec3.y }, z{ _vec3.z }, w{ _w } {}

		vec4(const vec4& _vec4) : x{ _vec4.x }, y{ _vec4.y }, z{ _vec4.z }, w{ _vec4.w } {}

		vec4& operator=(const vec4& rhs);
		vec4 operator*(const vec4& rhs) const;
		vec4 operator*(float scalar) const;
		vec4 operator+(const vec4& rhs) const;
		vec4 operator+(float scalar) const;
		vec4 operator-(const vec4& rhs) const;
		vec4 operator-(float scalar) const;
		void norm();

	};

	struct mat3x3
	{
		float a11, a12, a13, a21, a22, a23, a31, a32, a33;
		
		mat3x3() 
		{
			a11 = 1.0f; a12 = 0.0f; a13 = 0.0f;
			a21 = 0.0f; a22 = 1.0f; a23 = 0.0f;
			a31 = 0.0f; a32 = 0.0f; a33 = 1.0f;
		}

		mat3x3& operator=(const mat3x3& rhs);
		vec3   operator*(const vec3& rhs) const;
		mat3x3 operator*(float scalar) const;
		mat3x3 operator*(const mat3x3& rhs) const;
		vec3   operator[](int idx) const;
		void   rotate(float angle, int axis);

	};

	struct mat4x4
	{
		float a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44;

		mat4x4()
		{
			a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
			a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = 0.0f;
			a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = 0.0f;
			a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
		}
		mat4x4& operator=(const mat4x4& rhs);
		vec4   operator*(const vec4& rhs) const;
		mat4x4 operator*(float scalar) const;
		mat4x4 operator*(const mat4x4& rhs) const;
		vec4   operator[](int idx) const;
		void   rotate(float angle, int axis);
		void   translate(vec3 distance);

	};

}