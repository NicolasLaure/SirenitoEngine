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

void Tank::Update(Input* inputInstance)
{
	tankModel->transform->ChildCount();

	float dirX = 0;
	float dirZ = 0;

	if (inputInstance->isKeyPressed(Keys::NUMPAD_8))
		dirZ = 1;
	else if (inputInstance->isKeyPressed(Keys::NUMPAD_2))
		dirZ = -1;

	if (inputInstance->isKeyPressed(Keys::NUMPAD_4))
		dirX = -1;
	else if (inputInstance->isKeyPressed(Keys::NUMPAD_6))
		dirX = 1;

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

			lCannon->Rotate(turret->GetRight(), rotationDir * cannonsSpeed);
			rCannon->Rotate(turret->GetRight(), rotationDir * cannonsSpeed);
		}
	}
	Vector3 movementDir = tankModel->transform->GetForward() * dirZ + tankModel->transform->GetRight() * dirX;
	tankModel->transform->Translate(movementDir);
}
