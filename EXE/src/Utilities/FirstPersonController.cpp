#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(Vector3 initialPosition, Camera* camera)
{
	this->camera = camera;
	camera->Translate(initialPosition.ToGlm());
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

	glm::vec3 dir = glm::vec3(dirX, dirY, dirZ);
	camera->Translate(dir * speed);

}
