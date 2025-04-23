#pragma once
#include "BaseGame/BaseGame.h"
#include <vector>
#include "Environment/Rock.h"
#include "Utilities/FirstPersonController.h"
#include "Entity/Entity3D/Mesh.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Sprite* background;
	Sprite* ground;
	Mesh* cube;
	FirstPersonController* camera;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};