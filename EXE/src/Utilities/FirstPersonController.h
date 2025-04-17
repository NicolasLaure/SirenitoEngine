#pragma once
#include "Input/Input.h"
#include "Utilities/Vector3.h"
#include "Camera/Camera.h"
#include "Entity/Entity2D/Sprite/Sprite.h"

class FirstPersonController
{
private:
	float speed = 0.5f;
	float mouseSensitivity = 10.0f;
	Camera* camera;

	float pitch = 0;
	float yaw = 0;
public:
	Sprite3D* sprite;

	FirstPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance);
	~FirstPersonController();
	void Update(Input* inputInstance);
};