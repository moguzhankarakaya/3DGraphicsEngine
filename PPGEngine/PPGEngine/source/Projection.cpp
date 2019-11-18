#include "Projection.h"


PPG::Projection::Projection(float aspectRatio, float fieldOfViewAngle, float nearPlane, float farPlane) :
	ar{ aspectRatio }, fov{ tan(Math::Conversions::DegreeToRad(fieldOfViewAngle / 2.0f)) }, n{ nearPlane }, f{ farPlane } 
{
	CalculateOrthographicProjection();
	CalculatePerspectiveProjection();
}

void PPG::Projection::CalculateOrthographicProjection()
{

}

void PPG::Projection::CalculatePerspectiveProjection()
{
	perspectiveProjection.a11 =  1.0f / (ar * fov);
	perspectiveProjection.a22 =  1.0f / (fov);
	perspectiveProjection.a33 = -1.0f * (f + n) / (f - n);
	perspectiveProjection.a34 =  2.0f * f * n / (f - n);
	perspectiveProjection.a43 = -1.0f;
	perspectiveProjection.a44 =  0.0f;
}
