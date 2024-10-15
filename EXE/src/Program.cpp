#include "Program.h"
#include "libs/glm/glm.hpp"
#include "Textures/Importer/TextureImporter.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float sansSize = 250;
	sans = new Sprite(glm::vec3(width / 2.0f, height / 2.0f, 0.0f), glm::vec3(0.0f), sansSize, sansSize, rendererInstance);
	sans->SetTexture("res/textures/sans-dance.jpg");
}

Program::~Program()
{
}

void Program::Update()
{
	sans->Scale(glm::vec3(sansScaleRatio, sansScaleRatio, sansScaleRatio));

	if (sans->GetScale().x < 1 || sans->GetScale().x > 3)
	{
		sansScaleRatio *= -1;
	}
}

void Program::Draw()
{
	sans->Draw();
}
