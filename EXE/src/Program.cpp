#include "Program.h"
#include "libs/glm/glm.hpp"
#include "Textures/Importer/TextureImporter.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float sansSize = 150;
	sans = new Sprite(glm::vec3(width / 2.0f, height / 2.0f - sansSize, 0.0f), glm::vec3(0.0f), sansSize, sansSize, rendererInstance);
	sans->SetTexture("res/textures/sans-dance.jpg");

	float friskSize = 40;
	heart = new Sprite(glm::vec3(width / 2.0f, height / 2.0f + friskSize, 0.0f), glm::vec3(0.0f), friskSize, friskSize, rendererInstance);
	heart->SetTexture("res/textures/heart.png");

	background = new Sprite(glm::vec3(width / 2.0f, height / 2.0f, 0.0f), glm::vec3(0.0f), width, height, rendererInstance);
	background->SetTexture("res/textures/background.png");
}

Program::~Program()
{
	delete sans;
	delete heart;
	delete background;
}

void Program::Update()
{
	sans->Scale(glm::vec3(sansScaleRatio, sansScaleRatio, sansScaleRatio));

	if (sans->GetScale().x < 1 || sans->GetScale().x > 3)
	{
		sansScaleRatio *= -1;
	}


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

	dir = glm::vec3(xAxis,yAxis,0.0f);

	heart->Translate(dir * heartSpeed);
}

void Program::Draw()
{
	background->Draw();
	sans->Draw();
	heart->Draw();
}
