#include "FirstPersonController.h"
#include "math.h"
#include <iostream>

FirstPersonController::FirstPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance)
{
	this->camera = camera;
	sprite = new Sprite3D("res/textures/sans-dance.jpg", initialPosition, Vector3(), 32, 32, rendererInstance);
}

FirstPersonController::~FirstPersonController()
{
	delete sprite;
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

	pitch += mouseDir.y * mouseSensitivity;
	yaw += mouseDir.x * mouseSensitivity;

	Vector3 movementDir = camera->view->GetForward() * dirZ;

	if (movementDir != Vector3::Zero())
	{
		camera->view->Translate(movementDir * speed);
	}
	Quaternion xRot = Quaternion::AngleAxis(pitch, camera->view->GetRight());
	Quaternion yRot = Quaternion::AngleAxis(yaw, camera->view->GetUp());

	camera->view->SetRotation(yRot * xRot);

	//sprite->SetPosition(transform->GetPosition());

	//if (inputInstance->isKeyPressed(Keys::Q))
	//	camera->view->Rotate(camera->view->GetUp(), 15);
	//else if (inputInstance->isKeyPressed(Keys::E))
	//	camera->view->Rotate(camera->view->GetUp(), -15);

	//sprite->SetRotation(transform->GetRotation());
}
