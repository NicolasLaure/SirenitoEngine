#pragma once
#include "DLL/BaseGame/BaseGame.h"
#include "DLL/Entity/Entity2D/Shape/Shape.h"
#include "DLL/Entity/Entity2D/Shape/Shapes/Rectangle.h"
#include "DLL/Entity/Entity2D/Shape/Shapes/Triangle.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Rectangle* blueSquare;

	glm::vec3 sqRightUpperCorner;
	glm::vec3 sqRightBottomCorner;
	glm::vec3 sqLeftBottomCorner;
	glm::vec3 sqLeftUpperCorner;

	glm::vec3 squareTranslateDirection;
	float squareTranslateSpeed;

	//---------------------------------------------------------------------------------

	Rectangle* pinkSquare;

	float pinkSquareSize;
	float scaleRatio;

	//----------------------------------------------------------------------------------------------------------

	Triangle* orangeTriangle;

	float triangleBase;
	float triangleHeight;

	glm::vec3 triRightUpperCorner;
	glm::vec3 triRightBottomCorner;

	float yDirection;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};