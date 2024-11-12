#include "Program.h"
#include "Textures/Importer/TextureImporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"
#include "Collisions/CollisionManager.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float knucklesSize = 100;
	float rockSize = 70;
	float rockVerticalOffset = 10;
	float rockHorizontalOffset = 140;
	knuckles = new Knuckles(knucklesSize, Vector3(width / 2.0f, height / 2.0f, 0.0f), rendererInstance);
	rock = new Rock(rockSize, Vector3(width / 2.0f + rockHorizontalOffset, (height / 2.0f) + rockVerticalOffset, 0.0f), rendererInstance);
}

Program::~Program()
{
	delete knuckles;
	delete rock;
}

void Program::Update()
{
	knuckles->Update(inputInstance);
	knuckles->CheckCollision(*rock->GetEntity());
}

void Program::Draw()
{
	knuckles->Draw();
	rock->Draw();
}
