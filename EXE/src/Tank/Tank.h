#pragma once
#include "Entity/Entity3D/Model.h"
#include "Input/Input.h"

class Tank
{
private:
	Model* tankModel;
	float turretSpeed = 5.0f;
	float cannonsSpeed = 0.25f;
	float cannonsAngle = 0;

	Transform* turret;
	Transform* lCannon;
	Transform* rCannon;
public:
	Tank(const char* modelPath, Vector3 position, Renderer* rendererInstance);
	Tank(Model* tankModel);
	~Tank();
	void Draw();
	void Update(Input* inputInstance);
};