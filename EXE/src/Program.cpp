#include "Program.h"
#include "libs/glm/glm.hpp"
#include "Textures/Importer/TextureImporter.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float sansSize = 150;
	sans = new Sprite("res/textures/sansAnim.png", glm::vec3(width / 2.0f, height / 2.0f - sansSize, 0.0f), glm::vec3(0.0f), sansSize, sansSize, rendererInstance);
	sans->SetAnimation("res/textures/sansAnim.png", { 0,140 }, 80, 140, 4, true);

	float friskSize = 40;
	heart = new Sprite("res/textures/heart.png", glm::vec3(width / 2.0f, height / 2.0f + friskSize, 0.0f), glm::vec3(0.0f), friskSize, friskSize, rendererInstance);

	background = new Sprite("res/textures/background.png", glm::vec3(width / 2.0f, height / 2.0f, 0.0f), glm::vec3(0.0f), width, height, rendererInstance);
}

Program::~Program()
{
	delete sans;
	delete heart;
	delete background;
}

void Program::Update()
{
	glm::vec3 dir = glm::vec3(0.0f);
	float xAxis = 0;
	float yAxis = 0;
	if (inputInstance->isKeyPressed(Keys::A))
		xAxis = -1.0f;
	if (inputInstance->isKeyPressed(Keys::D))
		xAxis = 1.0f;

	if (inputInstance->isKeyPressed(Keys::W))
		yAxis = -1.0f;
	if (inputInstance->isKeyPressed(Keys::S))
		yAxis = 1.0f;

	dir = glm::vec3(xAxis, yAxis, 0.0f);

	heart->Translate(dir * heartSpeed);
}

void Program::Draw()
{
	background->Draw();
	sans->Draw();
	heart->Draw();
}
