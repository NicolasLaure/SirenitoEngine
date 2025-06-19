#include "FirstPersonController.h"
#include "math.h"
#include <iostream>

FirstPersonController::FirstPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance)
{
	this->camera = camera;
	pivot = new Transform("camera", initialPosition, Quaternion::identity(), Vector3::One());
}

FirstPersonController::~FirstPersonController()
{
	delete pivot;
}

void FirstPersonController::Update(Input* inputInstance)
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

	Vector3 movementDir = pivot->GetForward() * dirZ + pivot->GetRight() * dirX;

	if (movementDir != Vector3::Zero())
		pivot->Translate(movementDir * speed);

	pivot->Rotate(pivot->GetUp(), yaw);
	camera->view->Rotate(Vector3::Right(), pitch);
}

void FirstPersonController::SetFirstPerson()
{
	camera->view->SetParent(pivot);
	camera->view->SetPosition(pivot->GetPosition());
	camera->view->SetLocalRotation(Quaternion::identity());
}

Transform* FirstPersonController::GetPivot()
{
	return pivot;
}
