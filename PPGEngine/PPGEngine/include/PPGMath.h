#pragma once
#include <cmath>
#include <cassert>
#include <limits>

namespace PPG
{	
	namespace Math
	{
		const float PI = 3.1415927f;
		const float EPSILON = 1.e-6f;
		struct vec2;
		struct vec3;
		struct vec4;
		struct mat3x3;
		struct mat4x4;
		
		struct Conversions 
		{
			static float DegreeToRad(float deg) { return deg * PI / 180.0f; }
			static float RadToDegree(float rad) { return rad * 180.0f / PI; }
		};

		struct vec2
		{
			union
			{
				struct { float x, y; };
				struct { float u, v; };
				float p[2] = { 0.0f, 0.0f };
			};

			vec2(float _x = 0.0f, float _y = 0.0f) : x{ _x }, y{ _y } {}

			vec2(const vec2& _vec2) : x{ _vec2.x }, y{ _vec2.y } { }

			vec2& operator=(const vec2& rhs);
			float operator*(const vec2& rhs) const;
			vec2  operator*(float scalar) const;
			vec2  operator+(const vec2& rhs) const;
			vec2  operator+(float scalar) const;
			vec2  operator-(const vec2& rhs) const;
			vec2  operator-(float scalar) const;
			vec2  operator/(float scalar) const;
			float operator[](int idx) const;
			float magnitude() const;
			float anglebetween(const vec2& rhs) const;
			void  normalize();
		};

		struct vec3
		{
			union
			{
				struct { float x, y, z; };
				struct { float u, v, w; };
				struct { float pitch, yaw, roll;};
				float p[3] = { 0.0f, 0.0f, 0.0f };
			};

			vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x{ _x }, y{ _y }, z{ _z } {}
			
			vec3(const vec3& _vec3) : x{ _vec3.x }, y{ _vec3.y }, z{ _vec3.z } { }

			vec3& operator=(const vec3& rhs);
			float operator*(const vec3& rhs) const;
			vec3  operator*(const float scalar) const;
			vec3& operator*=(const float scalar);
			vec3  operator+(const vec3& rhs) const;
			vec3& operator+=(const vec3& rhs);
			vec3  operator+(const float scalar) const;
			vec3& operator+=(const float scalar);
			vec3  operator-(const vec3& rhs) const;
			vec3& operator-=(const vec3& rhs);
			vec3  operator-(const float scalar) const;
			vec3& operator-=(const float scalar);
			vec3  operator/(const float scalar) const;
			vec3& operator/=(const float scalar);
			float operator[](const int idx) const;
			vec3  cross(const vec3& rhs) const;
			vec3  outer(const vec3& rhs) const;
			float magnitude() const;
			float anglebetween(const vec3& rhs) const;
			vec4  homogenize(const float w) const;
			void  normalize();

		};

		struct vec4
		{
			union
			{
				struct { float x, y, z, w; };
				float p[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			};

			vec4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}

			vec4(const vec3& _vec3, float _w) : x{ _vec3.x }, y{ _vec3.y }, z{ _vec3.z }, w{ _w } {}

			vec4(const vec4& _vec4) : x{ _vec4.x }, y{ _vec4.y }, z{ _vec4.z }, w{ _vec4.w } {}

			vec4& operator=(const vec4& rhs);
			float operator*(const vec4& rhs) const;
			vec4  operator*(const float scalar) const;
			vec4& operator*=(const float scalar);
			vec4  operator+(const vec4& rhs) const;
			vec4& operator+=(const vec4& rhs);
			vec4  operator+(const float scalar) const;
			vec4& operator+=(const float scalar);
			vec4  operator-(const vec4& rhs) const;
			vec4& operator-=(const vec4& rhs);
			vec4  operator-(const float scalar) const;
			vec4& operator-=(const float scalar);
			vec4  operator/(const float scalar) const;
			vec4& operator/=(const float scalar);
			float operator[](const int idx) const;
			vec4  outer(const vec4& rhs) const;
			vec3  cartesian() const;
			void  homogenize();
			void  normalize();

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
			vec3   operator[](const int idx) const;
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
}