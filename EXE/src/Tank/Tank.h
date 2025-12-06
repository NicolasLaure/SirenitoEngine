#pragma once
#include "Entity/Entity3D/Model.h"
#include "Input/Input.h"
#include "Frustum/Frustum.h"

class Tank
{
private:
	Model* tankModel;
	float speed = 0.5f;
	float turretSpeed = 1.25f;
	float cannonsSpeed = 0.25f;
	float cannonsAngle = 0;

	Transform* turret;
	Transform* lCannon;
	Transform* rCannon;

	Frustum* frustum;
public:
	Tank(const char* modelPath, Vector3 position, Frustum* frustum, Renderer* rendererInstance);
	Tank(Model* tankModel);
	~Tank();
	void Draw();
	void Update(Input* inputInstance);
};