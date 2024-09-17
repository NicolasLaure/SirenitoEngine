#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Shape/Shape.h"

SIRENITO_API class BaseGame
{
protected:
	Shape* rectangle = nullptr;
public:
	SIRENITO_API BaseGame();
	SIRENITO_API void RunProgram(int width, int height, const char* title);
	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();
};