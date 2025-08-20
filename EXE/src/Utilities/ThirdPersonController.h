#pragma once
#include "Input/Input.h"
#include "Utilities/Vector3.h"
#include "Camera/Camera.h"
#include "Entity/Entity3D/Cube.h"

class ThirdPersonController
{
private:
	float speed = 0.5f;
	float mouseSensitivity = 10.0f;
	Camera* camera;
	Transform* pivot;

	float pitch = 0;
	float yaw = 0;

	float meshAngle = 0;

	Vector3 cameraOffset;

	void UpdateCameraPosition();
public:
	Cube* mesh = nullptr;

	ThirdPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance);
	~ThirdPersonController();
	void Update(Input* inputInstance);

	void SetThirdPerson(Vector3 offset);
};