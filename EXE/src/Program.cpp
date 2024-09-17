#include "Program.h"
#include "libs/glm/glm.hpp"

Program::Program() : BaseGame()
{
}

void Program::Update()
{
	//rectangle->Translate(glm::vec3(2.0f, 1.0f, 0.0f));
	rectangle->Rotate(glm::vec3(0.0f, 0.0f, 20.0f));
}

void Program::Draw()
{
	rectangle->Draw();
}
