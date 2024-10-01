#include "Program.h"
#include "libs/glm/glm.hpp"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	rectangle = new Rectangle(glm::vec3(100.0f, 50.0f, 0.0f), 100.0f, 100.0f, Color::blue(), rendererInstance);
	triangle = new Triangle(glm::vec3(300.0f, 120.0f, 0.0f), 200.0f, 125.0f, Color(1.0f, 1.0f, 0.0f, 1.0f), rendererInstance);
}

Program::~Program()
{
	delete rectangle;
	delete triangle;
}

void Program::Update()
{
	if (inputInstance->isKeyPressed(Keys::A))
		rectangle->Translate(glm::vec3(-100.0f, 0.0f, 0.0f));

	rectangle->Rotate(glm::vec3(0.0f, 0.0f, 20.0f * deltaTime));
}

void Program::Draw()
{
	rectangle->Draw();
	triangle->Draw();
}
