#include "Program.h"
#include "libs/glm/glm.hpp"
#include "Textures/Importer/TextureImporter.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	sprite = new Sprite(200, 200, Color(1.0f, 0.6f, 0.4f, 0.5f), rendererInstance);
	sprite->SetTexture("res/textures/container.jpg");

	sans = new Sprite(glm::vec3(400.0f, 40.0f, 0.0f), glm::vec3(0), 250, 250, Color::white(), rendererInstance);
	sans->SetTexture("res/textures/sans-dance.jpg");
}

Program::~Program()
{
}

void Program::Update()
{
	sprite->Translate(glm::vec3(10.0f, 0.0f, 0.0f));
	//sans->Translate(glm::vec3(-10.0f, 0.0f, 0.0f));
}

void Program::Draw()
{
	sprite->Draw();
	sans->Draw();
}
