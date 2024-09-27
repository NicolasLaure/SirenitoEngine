#include "Program.h"
#include "libs/glm/glm.hpp"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float blueSquareSize = 70.0f;
	float spacing = 30.0f;

	sqRightUpperCorner = glm::vec3(width - blueSquareSize / 2 - spacing, blueSquareSize / 2 + spacing, 0.0f);
	sqRightBottomCorner = glm::vec3(width - blueSquareSize / 2 - spacing, height - blueSquareSize / 2 - spacing, 0.0f);
	sqLeftBottomCorner = glm::vec3(blueSquareSize / 2 + spacing, height - blueSquareSize / 2 - spacing, 0.0f);
	sqLeftUpperCorner = glm::vec3(blueSquareSize / 2 + spacing, blueSquareSize / 2 + spacing, 0.0f);

	squareTranslateSpeed = 7.0f;
	squareTranslateDirection = glm::vec3(0.0f, squareTranslateSpeed, 0.0f);

	blueSquare = new Rectangle(sqLeftUpperCorner, blueSquareSize, blueSquareSize, Color::blue(), rendererInstance);

	//----------------------------------------------------------------------------------------------------------

	pinkSquareSize = 70.0f;

	pinkSquare = new Rectangle(glm::vec3(width / 2, height / 2, 0.0f), pinkSquareSize, pinkSquareSize, Color(1.0f, 0.55f, 0.75f, 1.0f), rendererInstance);

	scaleRatio = 0.1f;

	//----------------------------------------------------------------------------------------------------------

	triangleBase = 100.0f;
	triangleHeight = 90.0f;

	triRightUpperCorner = glm::vec3(width / 2 + triangleBase + spacing * 4, triangleHeight / 2 + spacing, 0.0f);
	triRightBottomCorner = glm::vec3(width / 2 + triangleBase + spacing * 4, height - triangleHeight / 2 - spacing, 0.0f);

	orangeTriangle = new Triangle(triRightUpperCorner, triangleBase, triangleHeight, Color(1.0f, 0.64f, 0.0f, 1.0f), rendererInstance);

	yDirection = 7.0f;
}

Program::~Program()
{
	delete blueSquare;
	delete pinkSquare;
	delete orangeTriangle;
}

void Program::Update()
{
	blueSquare->Rotate(glm::vec3(0.0f, 0.0f, -3.0f));
	blueSquare->Translate(squareTranslateDirection);

	if (blueSquare->GetPosition().y > sqLeftBottomCorner.y)
	{
		blueSquare->SetPosition(sqLeftBottomCorner);
		squareTranslateDirection = glm::vec3(squareTranslateSpeed, 0.0f, 0.0f);
	}
	else if (blueSquare->GetPosition().x > sqRightBottomCorner.x)
	{
		blueSquare->SetPosition(sqRightBottomCorner);
		squareTranslateDirection = glm::vec3(0.0f, -squareTranslateSpeed, 0.0f);
	}
	else if (blueSquare->GetPosition().y < sqRightUpperCorner.y)
	{
		blueSquare->SetPosition(sqRightUpperCorner);
		squareTranslateDirection = glm::vec3(-squareTranslateSpeed, 0.0f, 0.0f);
	}
	else if (blueSquare->GetPosition().x < sqLeftUpperCorner.x)
	{
		blueSquare->SetPosition(sqLeftUpperCorner);
		squareTranslateDirection = glm::vec3(0.0f, squareTranslateSpeed, 0.0f);
	}

	//----------------------------------------------------------------------------------------------------------

	pinkSquare->Scale(glm::vec3(scaleRatio, scaleRatio, scaleRatio));

	if (pinkSquare->GetScale().x < 1 || pinkSquare->GetScale().x > 3)
	{
		scaleRatio *= -1;
	}

	//----------------------------------------------------------------------------------------------------------

	orangeTriangle->Translate(glm::vec3(0.0f, yDirection, 0.0f));

	if (orangeTriangle->GetPosition().y > triRightBottomCorner.y || orangeTriangle->GetPosition().y < triRightUpperCorner.y)
	{
		yDirection *= -1;
		orangeTriangle->Rotate(glm::vec3(0.0f, 0.0f, 3.14f));
	}
}

void Program::Draw()
{
	blueSquare->Draw();
	pinkSquare->Draw();
	orangeTriangle->Draw();
}
