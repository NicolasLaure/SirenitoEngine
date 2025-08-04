#pragma once
#include "Input/Input.h"
#include "Utilities/Vector3.h"
#include "Camera/Camera.h"
#include "Entity/Entity2D/Sprite/Sprite.h"

class FirstPersonController
{
private:
	float speed = 0.1f;
	float mouseSensitivity = 15.0f;
	Camera* camera;
	Transform* pivot;

	float pitch = 0;
	float yaw = 0;
public:
	FirstPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance);
	~FirstPersonController();
	void Update(Input* inputInstance);
	void SetFirstPerson();

	Transform* GetPivot();
};