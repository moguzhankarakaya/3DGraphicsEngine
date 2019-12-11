#include "Camera.h"

PPG::Camera::Camera(Math::vec3 initialPos, Math::vec3 worldUpVec, float cameraMoveSpeed, float cameraRotationSpeed) :
	eyePosition{ initialPos }, worldUp{ worldUpVec }, moveSpeed{ cameraMoveSpeed }, rotationSpeed{ cameraRotationSpeed }
{
	front = Math::vec3{ 0.0f, 0.0f, -1.0f };
	up    = worldUp;
	yaw = pitch = roll = 0.0f;

	updateCamera();
}

PPG::Math::mat4x4 PPG::Camera::getLookAtMatrix()
{
	Math::mat4x4 lookAt;

	lookAt.a11 = right.x; lookAt.a12 = up.x; lookAt.a13 = front.x; lookAt.a14 = eyePosition.x;
	lookAt.a21 = right.y; lookAt.a22 = up.y; lookAt.a23 = front.y; lookAt.a24 = eyePosition.y;
	lookAt.a31 = right.z; lookAt.a32 = up.z; lookAt.a33 = front.z; lookAt.a34 = eyePosition.z;

	return lookAt;
}

PPG::Math::mat4x4 PPG::Camera::getViewMatrix()
{
	Math::mat4x4 view;

	view.a11 = right.x; view.a12 = right.y; view.a13 = right.z; view.a14 = right * eyePosition * -1;
	view.a21 = up.x;    view.a22 = up.y;    view.a23 = up.z;    view.a24 = up    * eyePosition * -1;
	view.a31 = front.x; view.a32 = front.y; view.a33 = front.z; view.a34 = front * eyePosition * -1;

	return view;
}

PPG::Math::vec3 PPG::Camera::getCameraPos()
{
	return eyePosition;
}

PPG::Math::vec3 PPG::Camera::getForwardDir()
{
	return front;
}

PPG::Math::vec3 PPG::Camera::getRightDir()
{
	return right;
}

PPG::Math::vec3 PPG::Camera::getUpDir()
{
	return up;
}

PPG::Math::vec3 PPG::Camera::getWorldUpDir()
{
	return worldUp;
}

void PPG::Camera::MoveCamera(const Math::vec3 & translation)
{
	eyePosition += translation * moveSpeed;
}

void PPG::Camera::TiltCamera(float theta)
{
	pitch += theta * rotationSpeed;
	pitch = (pitch >  80.0f) ?  80.0f : pitch;
	pitch = (pitch < -80.0f) ? -80.0f : pitch;
	updateCamera();
}

void PPG::Camera::PanCamera(float theta)
{
	yaw += theta * rotationSpeed;
	yaw = (yaw > 360.0f) ? yaw - 360.0f : yaw;
	updateCamera();
}

void PPG::Camera::ResetCamera()
{
	eyePosition = Math::vec3{ 0.0f, 0.0f, 0.0f };
	front = Math::vec3{ 0.0f, 0.0f, -1.0f };
	up = worldUp;
	yaw = pitch = roll = 0.0f;

	updateCamera();
}

PPG::Camera::~Camera()
{
}

void PPG::Camera::updateCamera()
{
	front.x =      sin(Math::Conversions::DegreeToRad(yaw)) * cos(Math::Conversions::DegreeToRad(pitch));
	front.y =      sin(Math::Conversions::DegreeToRad(pitch));
	front.z = -1 * cos(Math::Conversions::DegreeToRad(yaw)) * cos(Math::Conversions::DegreeToRad(pitch));
	front.normalize();
	
	right = worldUp.cross(front);
	right.normalize();

	up = front.cross(right);
	up.normalize();
}
