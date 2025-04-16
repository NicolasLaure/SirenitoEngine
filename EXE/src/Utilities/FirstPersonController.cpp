#include "FirstPersonController.h"
#include "math.h"
#include <iostream>

FirstPersonController::FirstPersonController(Vector3 initialPosition, Camera* camera)
{
	this->camera = camera;
}

void FirstPersonController::Update(Input* inputInstance)
{
	float dirX = 0;
	float dirY = 0;
	float dirZ = 0;

	if (inputInstance->isKeyPressed(Keys::W))
		dirZ = -1;
	else if (inputInstance->isKeyPressed(Keys::S))
		dirZ = 1;

	if (inputInstance->isKeyPressed(Keys::A))
		dirX = -1;
	else if (inputInstance->isKeyPressed(Keys::D))
		dirX = 1;

	if (inputInstance->isKeyPressed(Keys::SPACE))
		dirY = 1;
	else if (inputInstance->isKeyPressed(Keys::LEFT_CONTROL))
		dirY = -1;

	Vector2 rotationDir = inputInstance->GetMouseDir();

	angleX += rotationDir.y * mouseSensitivity;
	angleY += rotationDir.x * mouseSensitivity;

	Vector3 dir = Vector3(dirX, dirY, dirZ);
	camera->Translate(dir * speed);
	//transform = MY4X4::TRS(pos, Quaternion::Euler(angleX, angleY, 0), Vector3::One());
	camera->Rotate(camera->view->GetRight(), rotationDir.y * mouseSensitivity);
	camera->Rotate(Vector3::Up(), rotationDir.x * mouseSensitivity);
}
