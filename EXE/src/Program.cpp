#include "Program.h"
#include "libs/glm/glm.hpp"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float triangleSideSize = 100.0f;
	leftTriangle = new Triangle(glm::vec3(0.0f + triangleSideSize / 2, 0.0f + triangleSideSize / 2, 0.0f), triangleSideSize, triangleSideSize, Color(1.0f, 1.0f, 0.0f, 1.0f), rendererInstance);
	rightTriangle = new Triangle(glm::vec3(width - triangleSideSize / 2, height - triangleSideSize / 2, 0.0f), triangleSideSize, triangleSideSize, Color(1.0f, 0.0f, 1.0f, 1.0f), rendererInstance);
}

Program::~Program()
{
	delete leftTriangle;
	delete rightTriangle;
}

void Program::Update()
{
	leftTriangle->Translate(glm::vec3(0.0f, 4.0f, 0.0f));
	leftTriangle->Rotate(glm::vec3(0.0f, 0.0f, -0.2f));

	rightTriangle->Translate(glm::vec3(0.0f, -4.0f, 0.0f));
	rightTriangle->Rotate(glm::vec3(0.0f, 0.0f, 0.2f));
}

void Program::Draw()
{
	leftTriangle->Draw();
	rightTriangle->Draw();
}
