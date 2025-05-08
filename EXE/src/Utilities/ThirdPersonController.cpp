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
	float dirX = 0;
	float dirY = 0;
	float dirZ = 0;

	if (inputInstance->isKeyPressed(Keys::W))
		dirZ = 1;
	else if (inputInstance->isKeyPressed(Keys::S))
		dirZ = -1;

	if (inputInstance->isKeyPressed(Keys::A))
		dirX = 1;
	else if (inputInstance->isKeyPressed(Keys::D))
		dirX = -1;

	Vector2 mouseDir = inputInstance->GetMouseDir();

	pitch = mouseDir.y * mouseSensitivity;
	yaw = -mouseDir.x * mouseSensitivity;

	Vector3 movementDir = camera->view->GetForward() * dirZ + camera->view->GetRight() * dirX;

	if (movementDir != Vector3::Zero())
		mesh->transform->Translate(movementDir * speed);

	camera->view->RotateAround(mesh->transform->GetPosition(), mesh->transform->GetUp(), yaw);
}

void ThirdPersonController::SetThirdPerson(Vector3 offset)
{
	camera->view->SetParent(mesh->transform);
	camera->view->SetLocalPosition(mesh->transform->GetPosition() + offset);
}
