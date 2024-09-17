#pragma once
#include "DLL/BaseGame/BaseGame.h"
#include "DLL/Entity/Entity2D/Shape/Shape.h"

SIRENITO_API class Program : public BaseGame
{
public:
	Program();
	void Update() override;
	void Draw() override;
};