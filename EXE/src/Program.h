#pragma once
#include "BaseGame/BaseGame.h"
#include <vector>
#include "Environment/Rock.h"
#include "Utilities/FirstPersonController.h"
#include "Utilities/ThirdPersonController.h"
#include "Entity/Entity3D/Cube.h"
#include "Entity/Entity3D/Model.h"
#include "Tank/Tank.h"
#include "Collisions/BSP_scene/Scene.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Sprite* background;
	Sprite* ground;
	Cube* cube;
	Cube* cube2;
	Model* backpackModel;
	Model* mclarenmodel;
	Tank* tank;
	Scene* scene;

	FirstPersonController* firstPersonCamera;
	ThirdPersonController* thirdPersonCamera;
	bool isFirstPerson = true;

	float pointLightRotationSpeed = 3.0f;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};