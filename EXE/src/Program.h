#pragma once
#include "BaseGame/BaseGame.h"
#include <vector>
#include "Knuckles/Knuckles.h"
#include "Environment/Rock.h"
#include "Utilities/FirstPersonController.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Knuckles* knuckles;
	Rock* rock;
	Sprite* background;
	FirstPersonController* camera;
	
public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};