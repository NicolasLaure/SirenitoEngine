#include "Tank.h"
#include "AssetImporter/AssetImporter.h"
#include <iostream>

using namespace std;

Tank::Tank(const char* modelPath, Vector3 position, Renderer* rendererInstance)
{
	tankModel = new Model(modelPath, Material(), rendererInstance);
	tankModel->transform->SetLocalScale(Vector3(0.5f, 0.5f, 0.5f));
	tankModel->transform->SetPosition(position);

	turret = tankModel->transform->Find("Turret");
	lCannon = tankModel->transform->Find("LeftCannon");
	rCannon = tankModel->transform->Find("RightCannon");
}

Tank::~Tank()
{
	delete tankModel;
}

void Tank::Draw()
{
	tankModel->Draw();
}


Tank::Tank(Model* tankModel)
{
	this->tankModel = tankModel;

	turret = tankModel->transform->Find("Turret");
	lCannon = tankModel->transform->Find("LeftCannon");
	rCannon = tankModel->transform->Find("RightCannon");
}

void Tank::Update(Input* inputInstance)
{
	tankModel->transform->ChildCount();

	float dirX = 0;
	float dirY = 0;
	float dirZ = 0;

	if (inputInstance->isKeyPressed(Keys::NUMPAD_8))
		dirZ = 1;
	else if (inputInstance->isKeyPressed(Keys::NUMPAD_2))
		dirZ = -1;

	if (inputInstance->isKeyPressed(Keys::NUMPAD_4))
		dirX = -1;
	else if (inputInstance->isKeyPressed(Keys::NUMPAD_6))
		dirX = 1;

	if (inputInstance->isKeyPressed(Keys::DOWN))
		dirY = -1;
	else if (inputInstance->isKeyPressed(Keys::UP))
		dirY = 1;

	if (turret != nullptr)
	{
		if (inputInstance->isKeyPressed(Keys::NUMPAD_3))
			turret->Rotate(turret->GetUp(), turretSpeed);
		if (inputInstance->isKeyPressed(Keys::NUMPAD_1))
			turret->Rotate(turret->GetUp(), -turretSpeed);

		if (lCannon != nullptr && rCannon != nullptr)
		{
			int rotationDir = 0;
			if (inputInstance->isKeyPressed(Keys::NUMPAD_ADD))
				rotationDir = -1;
			if (inputInstance->isKeyPressed(Keys::NUMPAD_SUBTRACT))
				rotationDir = 1;

			cannonsAngle += rotationDir * cannonsSpeed;

			lCannon->SetLocalRotation(Quaternion::Euler(cannonsAngle, 0.0f, 0.0f));
			rCannon->SetLocalRotation(Quaternion::Euler(cannonsAngle, 0.0f, 0.0f));
		}
	}
	Vector3 movementDir = tankModel->transform->GetRight() * dirX + tankModel->transform->GetUp() * dirY + tankModel->transform->GetForward() * dirZ ;
	tankModel->transform->Translate(movementDir);
}
