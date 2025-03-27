#pragma once
#include "Input/Input.h"
#include "Utilities/Vector3.h"
#include "Camera/Camera.h"

class FirstPersonController
{
private:
	float speed = 10.0f;
	Camera* camera;

public:
	FirstPersonController(Vector3 initialPosition, Camera* camera);

	void Update(Input* inputInstance);
};