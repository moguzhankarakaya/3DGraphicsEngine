#pragma once
#include "PPGMath.h"

namespace PPG
{
	class Camera
	{
	public:
		Camera(Math::vec3 initialPos = Math::vec3(0.0f, 0.0f, 0.0f), 
			   Math::vec3 worldUp    = Math::vec3(0.0f, 1.0f, 0.0f), 
			   float cameraMoveSpeed = 1.0f, float cameraRotationSpeed = 1.0f);
		
		Math::mat4x4 getLookAtMatrix();
		Math::mat4x4 getViewMatrix();
		Math::vec3   getCameraPos();
		Math::vec3   getForwardDir();
		Math::vec3   getRightDir();
		Math::vec3   getUpDir();
		Math::vec3   getWorldUpDir();
		
		void MoveCamera(const Math::vec3& translation);
		void TiltCamera(float pitch);
		void PanCamera(float yaw);
		void RollCamera(float roll);
		void ResetCamera();

		~Camera();

	private:
		Math::vec3 right, up, front, worldUp;
		Math::vec3 eyePosition;
		float yaw, pitch, roll;
		float moveSpeed, rotationSpeed;

		void updateCamera();
	};
}