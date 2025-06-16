#include "ThirdPersonController.h"

ThirdPersonController::ThirdPersonController(Vector3 initialPosition, Camera* camera, Renderer* rendererInstance)
{
	this->camera = camera;
	mesh = new Cube("res/textures/sans-dance.jpg", initialPosition, Vector3(), rendererInstance);
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

	pitch += mouseDir.y * mouseSensitivity;
	yaw -= mouseDir.x * mouseSensitivity;


	if (dirZ != 0)
		mesh->transform->Translate(mesh->transform->GetForward() * dirZ * speed);
	if (dirX != 0)
	{
		meshAngle += dirX * speed * 10;
		mesh->transform->Rotate(mesh->transform->GetUp() * meshAngle);
	}

	UpdateCameraPosition();
}

void ThirdPersonController::SetThirdPerson(Vector3 offset)
{
	cameraOffset = offset;
	UpdateCameraPosition();
}


void ThirdPersonController::UpdateCameraPosition()
{
	camera->view->SetPosition(mesh->transform->GetPosition() + cameraOffset);

	camera->view->RotateAround(mesh->transform->GetPosition(), Vector3::Up(), yaw);
	camera->view->RotateAround(mesh->transform->GetPosition(), camera->view->GetRight(), pitch);
	camera->view->LookAt(Transform("Point", mesh->transform->GetPosition(), Quaternion::identity(), Vector3::One()));
}