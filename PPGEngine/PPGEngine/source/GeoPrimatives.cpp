#include "GeoPrimatives.h"

PPG::Triangle& PPG::Triangle::operator=(const Triangle & rhs)
{
	v[0]   = rhs.v[0];
	v[1]   = rhs.v[1];
	v[2]   = rhs.v[2];
	n[0]   = rhs.n[0];
	n[1]   = rhs.n[1];
	n[2]   = rhs.n[2];
	t[0]   = rhs.t[0];
	t[1]   = rhs.t[1];
	t[2]   = rhs.t[2];
	color  = rhs.color;
	symbol = rhs.symbol;

	return *this;
}

PPG::Triangle PPG::Triangle::operator*(const Math::mat4x4 transform) const
{
	Triangle result;
	
	result.v[0] = (transform * v[0]);
	result.v[1] = (transform * v[1]);
	result.v[2] = (transform * v[2]);
	
	result.t[0] = this->t[0] / abs(result.v[0].w);
	result.t[1] = this->t[1] / abs(result.v[1].w);
	result.t[2] = this->t[2] / abs(result.v[2].w);

	result.v[0].homogenize();
	result.v[1].homogenize();
	result.v[2].homogenize();
	
	result.color  = this->color;
	result.symbol = this->symbol;

	return result;
}

PPG::Math::vec4 PPG::Triangle::Normal() const
{
	Math::vec3 result;
	result = (v[1].cartesian() - v[0].cartesian()).cross(v[2].cartesian() - v[0].cartesian());
	result.normalize();
	Math::vec4 normalVector{ result, 0.0f };
	return normalVector;
}

PPG::Math::vec4 PPG::Triangle::Interpolate(float alpha1, float alpha2, float alpha3) const
{
	Math::vec4 result{ alpha1 * v[0].x + alpha1 * v[1].x + alpha1 * v[2].x ,
					   alpha1 * v[0].y + alpha1 * v[1].y + alpha1 * v[2].y ,
					   alpha1 * v[0].z + alpha1 * v[1].z + alpha1 * v[2].z ,
					   1.0f
					 };

	return result;
}

PPG::Math::vec4 PPG::Triangle::ViewVector(const Math::vec4 & viewpoint) const
{
	Math::vec4 result{ this->Interpolate(1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f) - viewpoint };
	result.w = 0.0f;

	return result;
}

PPG::Math::vec4 PPG::Triangle::Reflect(const Math::vec4 & incoming) const
{
	Math::vec4 result{ incoming + this->Normal() * ((incoming * -1.0f)* this->Normal()) * 2.0f };
	
	return result;
}

std::vector<PPG::Triangle> PPG::Triangle::ClipAgainst(const std::vector<Plane>& planes) const
{
	std::vector<Triangle> clippedTriangles{ *this };

	size_t trianglesToProcess = clippedTriangles.size();

	for (const auto& plane : planes)
	{
		trianglesToProcess = clippedTriangles.size();

		while (trianglesToProcess > 0)
		{
			Triangle triangle = clippedTriangles.front();
			clippedTriangles.erase(clippedTriangles.begin());
			trianglesToProcess--;

			/* START OF CLIPPING */
			float d0 = plane.Distance(triangle.v[0]);
			float d1 = plane.Distance(triangle.v[1]);
			float d2 = plane.Distance(triangle.v[2]);

			Math::vec4 pointsInside[3];  Math::vec3 textureCoordInside[3];  size_t sizePointsInside = 0;
			Math::vec4 pointsOutside[3]; Math::vec3 textureCoordOutside[3]; size_t sizePointsOutside = 0;

			if (d0 >= 0.0f)
			{
				pointsInside[sizePointsInside]   = triangle.v[0];
				textureCoordInside[sizePointsInside] = triangle.t[0];
				sizePointsInside++;
			}
			else
			{
				pointsOutside[sizePointsOutside] = triangle.v[0];
				textureCoordOutside[sizePointsOutside] = triangle.t[0];
				sizePointsOutside++;
			}

			if (d1 >= 0.0f)
			{
				pointsInside[sizePointsInside]   = triangle.v[1];
				textureCoordInside[sizePointsInside] = triangle.t[1];
				sizePointsInside++;
			}
			else
			{
				pointsOutside[sizePointsOutside] = triangle.v[1];
				textureCoordOutside[sizePointsOutside] = triangle.t[1];
				sizePointsOutside++;
			}

			if (d2 >= 0.0f)
			{
				pointsInside[sizePointsInside]	 = triangle.v[2];
				textureCoordInside[sizePointsInside] = triangle.t[2];
				sizePointsInside++;
			}
			else
			{
				pointsOutside[sizePointsOutside] = triangle.v[2];
				textureCoordOutside[sizePointsOutside] = triangle.t[2];
				sizePointsOutside++;
			}

			if (sizePointsInside == 3)
			{ 
				clippedTriangles.push_back(triangle);
			}
			else if (sizePointsInside == 2)
			{
				Math::vec4 pInside1 = pointsInside[0];
				Math::vec3 tCoorIn1 = textureCoordInside[0];
				Math::vec4 pInside2 = pointsInside[1];
				Math::vec3 tCoorIn2 = textureCoordInside[1];
				
				Math::vec4 pIntersection1 = plane.GetHitPoint(Line{ pInside1, pointsOutside[0] });
				float t1 = Line{ pInside1, pointsOutside[0] }.GetLineParamAt(pIntersection1);
				Math::vec3 tCoordIntersection1  = tCoorIn1 + (textureCoordOutside[0] - tCoorIn1) * t1;
				
				Math::vec4 pIntersection2 = plane.GetHitPoint(Line{ pInside2, pointsOutside[0] });
				float t2 = Line{ pInside2, pointsOutside[0] }.GetLineParamAt(pIntersection2);
				Math::vec3 tCoordIntersection2 = tCoorIn2 + (textureCoordOutside[0] - tCoorIn2) * t2;

				Triangle triangle1{ pInside1, pIntersection1, pIntersection2, this->color, this->symbol };
				triangle1.SetTextureCoordinates(tCoorIn1, tCoordIntersection1, tCoordIntersection2);
				Triangle triangle2{ pInside1, pIntersection2, pInside2,       this->color, this->symbol };
				triangle2.SetTextureCoordinates(tCoorIn1, tCoordIntersection2, tCoorIn2);
				clippedTriangles.push_back(triangle1);
				clippedTriangles.push_back(triangle2);
			}
			else if (sizePointsInside == 1)
			{
				Math::vec4 pIntersection1 = plane.GetHitPoint(Line{ pointsInside[0], pointsOutside[0] });
				float t1 = Line{ pointsInside[0], pointsOutside[0] }.GetLineParamAt(pIntersection1);
				Math::vec4 pIntersection2 = plane.GetHitPoint(Line{ pointsInside[0], pointsOutside[1] });
				float t2 = Line{ pointsInside[0], pointsOutside[1] }.GetLineParamAt(pIntersection2);
				Triangle triangle1{ pointsInside[0], pIntersection1, pIntersection2, this->color, this->symbol };
				triangle1.SetTextureCoordinates(textureCoordInside[0], 
											   textureCoordInside[0] + (textureCoordOutside[0] - textureCoordInside[0])*t1,
											   textureCoordInside[0] + (textureCoordOutside[1] - textureCoordInside[0])*t2);
				clippedTriangles.push_back(triangle1);
			}
			else
			{

			}
			/* END OF CLIPPING */
		}
	}

	return clippedTriangles;
}

float PPG::Line::GetLineParamAt(const Math::vec4 & point) const
{
	return (point - P0).cartesian().magnitude() / (P1 - P0).cartesian().magnitude();
}

float PPG::Line::Distance(const Math::vec4 & point) const
{
	return ((point - P0) - (dir * ((point - P0)*dir))).cartesian().magnitude();
}

PPG::Line PPG::Line::Normal(const Math::vec4 & point) const
{
	return Line{ ((point - P0) - (dir * ((point - P0)*dir))), point };
}

PPG::Math::vec4 PPG::Line::GetPointAt(float t) const
{
	return Math::vec4{ P0 + dir * t };
}

float PPG::Plane::Distance(const Math::vec4 & point) const
{
	return (point - P0) * n;
}

bool PPG::Plane::IsIntersected(const Line & line) const
{
	float t_num = (line.P0 - P0) * n;
	float t_denum = line.dir * n;
	if (-1 * Math::EPSILON > t_denum || t_denum > Math::EPSILON)
	{
		float t = t_num / t_denum;
		return true;
	}
	else
	{
		if (-1 * Math::EPSILON > t_num || t_num > Math::EPSILON)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool PPG::Plane::Contains(const Math::vec4 & point) const
{
	return (point - P0) * n == 0.0f;
}

PPG::Math::vec4 PPG::Plane::GetHitPoint(const Line & line) const
{
	return Math::vec4{ line.P0 + line.dir * ((P0 - line.P0) * n / (line.dir * n)) };
}
