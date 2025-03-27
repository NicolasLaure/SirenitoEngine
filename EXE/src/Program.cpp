#include "Program.h"
#include "Textures/Importer/TextureImporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"
#include "Collisions/CollisionManager.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	camera = new FirstPersonController(Vector3(0, 0, 500), mainCamera);

	float knucklesSize = 100;
	float rockSize = 70;
	float knucklesVerticalOffset = -25;
	float rockVerticalOffset = -20;
	float rockHorizontalOffset = 140;
	knuckles = new Knuckles(knucklesSize, Vector3(width / 2.0f, height / 2.0f + knucklesVerticalOffset, 10.0f), rendererInstance);
	rock = new Rock(rockSize, Vector3(width / 2.0f + rockHorizontalOffset, (height / 2.0f) + rockVerticalOffset, 0.0f), rendererInstance);

	background = new Sprite("res/textures/Background.jpg", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(), -width, -height, rendererInstance);
}

Program::~Program()
{
	delete knuckles;
	delete rock;
	delete background;
	delete camera;
}

void Program::Update()
{
	knuckles->CheckCollision(*rock->GetEntity());
	camera->Update(inputInstance);

	if (inputInstance->isKeyDown(Keys::F2))
	{
		hasPerspective = !hasPerspective;
		rendererInstance->SetProjection(hasPerspective);
	}
}

void Program::Draw()
{
	background->Draw();
	knuckles->Draw();
	rock->Draw();
}
