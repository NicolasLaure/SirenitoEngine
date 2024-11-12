#pragma once
#include "BaseGame/BaseGame.h"
#include <vector>
#include "Knuckles/Knuckles.h"
#include "Environment/Rock.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Knuckles* knuckles;
	Rock* rock;
	Sprite* background;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};