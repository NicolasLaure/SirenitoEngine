#include "Program.h"
#include "libs/glm/glm.hpp"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	glm::vec3 position = glm::vec3(100.0f, 50.0f, 0.0f);
	float rectangleWidth = 100.0f;
	float rectangleHeight = 100.0f;

Program::~Program()
{
	delete rectangle;
}

void Program::Update()
{
	rectangle->Translate(glm::vec3(400.0f * deltaTime, 100.0f * deltaTime, 0.0f));
	rectangle->Rotate(glm::vec3(0.0f, 0.0f, 20.0f * deltaTime));
}

void Program::Draw()
{
	rectangle->Draw();
}
