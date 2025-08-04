#pragma once
#include "Entity/Entity3D/Model.h"
#include "Input/Input.h"

class Tank
{
private:
	Model* tankModel;
	float turretSpeed = 0.5f;
	float cannonsSpeed = 0.25f;

	Transform* turret ;
	Transform* lCannon;
	Transform* rCannon;
public:
	Tank(const char* modelPath, Vector3 position, Renderer* rendererInstance);
	~Tank();
	void Draw();
	void Update(Input* inputInstance);
};