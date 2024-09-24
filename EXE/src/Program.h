#pragma once
#include "DLL/BaseGame/BaseGame.h"
#include "DLL/Entity/Entity2D/Shape/Shape.h"
#include "DLL/Entity/Entity2D/Shape/Shapes/Rectangle.h"
#include "DLL/Entity/Entity2D/Shape/Shapes/Triangle.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Triangle* leftTriangle;
	Triangle* rightTriangle;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};