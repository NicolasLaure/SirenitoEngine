#include "ThirdPersonController.h"

ThirdPersonController::ThirdPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance)
{
	this->camera = camera;
	mesh = new Mesh("res/textures/sans-dance.jpg", initialPosition, Vector3(), 32, 32, rendererInstance);
}

ThirdPersonController::~ThirdPersonController()
{
	delete mesh;
}

void ThirdPersonController::Update(Input* inputInstance)
{
}
