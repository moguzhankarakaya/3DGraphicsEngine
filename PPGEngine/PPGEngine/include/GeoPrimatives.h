#pragma once
#include <list>
#include <vector>

#include "PPGMath.h"

namespace PPG
{
	struct Triangle;
	struct Line;
	struct Plane;

	struct Triangle
	{
		Math::vec4 v[3];
		Math::vec4 n[3];
		Math::vec3 t[3];
		short      color;
		wchar_t    symbol;

		Triangle(const Math::vec4& v1 = Math::vec4(), const Math::vec4& v2 = Math::vec4(), const Math::vec4& v3 = Math::vec4(),
				 short   tri_color  = 0x00F0, 
				 wchar_t tri_symbol = 0x2588)
				 : v{ v1, v2, v3 },  color{ tri_color }, symbol{ tri_symbol } { }
		
		Triangle&   operator=(const Triangle& rhs);
		Triangle    operator*(const Math::mat4x4 transform) const;

		void SetTextureCoordinates(const Math::vec3& t1, const Math::vec3& t2, const Math::vec3& t3) { t[0] = t1; t[1] = t2; t[2] = t3; }
		void SetPerVertexNormals(const Math::vec4& n1, const Math::vec4& n2, const Math::vec4& n3) { n[0] = n1; n[1] = n2; n[2] = n3; }
				
		Math::vec4  Interpolate(float alpha1, float alpha2, float alpha3) const;
		Math::vec4  ViewVector(const Math::vec4& viewpoint = Math::vec4()) const;
		Math::vec4  Reflect(const Math::vec4& incoming) const;
		Math::vec4  Normal() const;
		
		std::vector<Triangle> ClipAgainst(const std::vector<Plane>& planes) const;

	};
	
	struct Line
	{
		Math::vec4 dir;
		Math::vec4 P0;
		Math::vec4 P1;

		Line(const Math::vec4& P1 = Math::vec4(), const Math::vec4& P2 = Math::vec4()) 
			: dir{ P2 - P1 }, P0{ P1 }, P1{ P2}
		{ dir.w = 0.0f; dir.normalize(); }
		
		float       GetLineParamAt(const Math::vec4& point) const;
		float       Distance(const Math::vec4& point) const;
		Line        Normal(const Math::vec4& point) const; 
		Math::vec4  GetPointAt(float t) const;
	};

	struct Plane
	{
		Math::vec4 n;
		Math::vec4 P0;

		Plane(const Math::vec4& normalToPlane = Math::vec4(), const Math::vec4& pointOnPlane = Math::vec4()) : 
			n{ normalToPlane }, P0{ pointOnPlane } 
		{ n.w = 0.0f; n.normalize(); }
		
		bool       IsIntersected(const Line& line) const;
		bool       Contains(const Math::vec4& point) const;
		
		float      Distance(const Math::vec4& point) const;
		
		Math::vec4 GetHitPoint(const Line& line) const;
	};
}