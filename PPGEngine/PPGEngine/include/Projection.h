#pragma once
#include "PPGMath.h"

namespace PPG
{
	class Projection
	{
	public:
		Projection(float aspectRatio, float fieldOfViewAngle, float nearPlane, float farPlane);

		Math::mat4x4& GetPerspectiveProjection() { return perspectiveProjection; }
		Math::mat4x4& GetOrthographicProjection() { return orthographicProjection; }

	private:
		void CalculatePerspectiveProjection();
		void CalculateOrthographicProjection();


		float ar, fov, n, f;
		Math::mat4x4 perspectiveProjection, orthographicProjection;
	};
}