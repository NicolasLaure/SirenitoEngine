#include "Program.h"
#include "Textures/Importer/TextureImporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float sansSize = 150;
	explosion = new Sprite("res/textures/Explosion-Sheet.png", Vector3(width / 2.0f, height / 2.0f - sansSize, 0.0f), Vector3(), sansSize, sansSize, rendererInstance);
	explosion->SetAnimation("res/textures/Explosion-Sheet.png", { 0,0 }, 32, 32, 5, 1, true);
	explosion->animation->Play();

	float friskSize = 40;
	heart = new Sprite("res/textures/heart.png", Vector3((float)width / 2.0f, (float)height / 2.0f + friskSize, 0.0f), Vector3(), friskSize, friskSize, rendererInstance);

	background = new Sprite("res/textures/background.png", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(), width, height, rendererInstance);
}

Program::~Program()
{
	delete explosion;
	delete heart;
	delete background;
}

void Program::Update()
{
	Vector3 dir = Vector3();
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

	if (inputInstance->isKeyDown(Keys::P))
		explosion->animation->Pause();
	if (inputInstance->isKeyDown(Keys::U))
		explosion->animation->Play();

	dir = Vector3(xAxis, yAxis, 0.0f);

	heart->Translate(dir * heartSpeed);
}

void Program::Draw()
{
	background->Draw();
	heart->Draw();
	explosion->Draw();
}
