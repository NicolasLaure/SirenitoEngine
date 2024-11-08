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

	sonic = new Sprite("res/textures/sonic.png", Vector3(width / 2.0f, height / 2.0f - sansSize, 0.0f), Vector3(), sansSize, sansSize, rendererInstance);
	sonic->SetAnimation("res/textures/sonic.png", { 5,0 }, 30, 37, 4, 1, true);
	sonic->animation->Play();

	float friskSize = 40;
	heart = new Sprite("res/textures/heart.png", Vector3((float)width / 2.0f, (float)height / 2.0f + friskSize, 0.0f), Vector3(), friskSize, friskSize, rendererInstance);

	background = new Sprite("res/textures/background.png", Vector3(width / 2.0f, height / 2.0f, 0.0f), Vector3(), width, height, rendererInstance);

	float wallHeight = 300;
	float wallWidth = 75;
	//right
	leftWall = new Sprite("", Vector3(190, height / 2.0f, 0.0f), Vector3(), wallWidth, wallHeight, rendererInstance);
	rightWall = new Sprite("", Vector3(444, height / 2.0f, 0.0f), Vector3(), wallWidth, wallHeight, rendererInstance);

	//upper
	wallHeight = 75;
	wallWidth = 400;
	upperWall = new Sprite("", Vector3(width / 2, 170, 0.0f), Vector3(), wallWidth, wallHeight, rendererInstance);
	//lower
	lowerWall = new Sprite("", Vector3(width / 2, 425, 0.0f), Vector3(), wallWidth, wallHeight, rendererInstance);
}

Program::~Program()
{
	delete explosion;
	delete heart;
	delete sonic;
	delete background;
	
	delete leftWall;
	delete rightWall;
	delete lowerWall;
	delete upperWall;
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
	
	heart->HandleCollision(*lowerWall);
	heart->HandleCollision(*leftWall);
	heart->HandleCollision(*rightWall);
	heart->HandleCollision(*upperWall);

	heart->SetPrevPos(heart->GetPosition());
}

void Program::Draw()
{
	background->Draw();
	heart->Draw();
	sonic->Draw();
	explosion->Draw();
}
