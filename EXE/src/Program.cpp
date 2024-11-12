#include "Program.h"
#include "Textures/Importer/TextureImporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	float spriteSize = 150;

	eirika = new Sprite("res/textures/Eirika.gif", Vector3(width / 4.0f * 3, height / 2.0f - spriteSize, 0.0f), Vector3(), spriteSize, spriteSize, rendererInstance);
	eirika->SetAnimation("res/textures/Eirika.gif", { 0, 191 }, 44, 61, 3, 1, true);

	hector = new Sprite("res/textures/Hector.gif", Vector3(width / 4.0f, height / 2.0f - spriteSize, 0.0f), Vector3(), spriteSize, spriteSize, rendererInstance);
	hector->SetAnimation("res/textures/Hector.gif", { 8, 289 }, 38, 58, 3, 1, true);
}

Program::~Program()
{
	delete eirika;
	delete hector;
}

void Program::Update()
{
	Vector3 eirikaDir = Vector3();
	float xAxisEirika = 0;
	float yAxisEirika = 0;

	Vector3 hectorDir = Vector3();
	float xAxisHector = 0;
	float yAxisHector = 0;

	bool eirikaAttacking = false;
	bool hectorAttacking = false;

	//-------------------------------------------------------------

	if (inputInstance->isKeyPressed(Keys::A))
		xAxisEirika = -1.0f;

	if (inputInstance->isKeyPressed(Keys::D))
		xAxisEirika = 1.0f;

	if (inputInstance->isKeyPressed(Keys::W))
		yAxisEirika = -1.0f;

	if (inputInstance->isKeyPressed(Keys::S))
		yAxisEirika = 1.0f;

	//----------------------------------------------------------------

	if (inputInstance->isKeyPressed(Keys::LEFT))
		xAxisHector = -1.0f;

	if (inputInstance->isKeyPressed(Keys::RIGHT))
		xAxisHector = 1.0f;

	if (inputInstance->isKeyPressed(Keys::UP))
		yAxisHector = -1.0f;

	if (inputInstance->isKeyPressed(Keys::DOWN))
		yAxisHector = 1.0f;

	eirikaDir = Vector3(xAxisEirika, yAxisEirika, 0.0f);
	hectorDir = Vector3(xAxisHector, yAxisHector, 0.0f);

	eirika->Translate(eirikaDir * 10);
	hector->Translate(hectorDir * 10);

	eirika->animation->Pause();
	hector->animation->Pause();

	if (inputInstance->isKeyPressed(Keys::P))
	{
		eirika->animation->Play();
		eirikaAttacking = true;
	}

	if (inputInstance->isKeyPressed(Keys::U))
	{
		hector->animation->Play();
		hectorAttacking = true;
	}

	//-------------------------------------------------------------

	if(hectorAlive)
		eirika->HandleCollision(*hector);

	if(eirikaAlive)
		hector->HandleCollision(*eirika);

	eirika->SetPrevPos(eirika->GetPosition());
	hector->SetPrevPos(hector->GetPosition());

	if (eirika->IsColliding())
	{
		if(eirikaAttacking && hectorAlive)
			hectorAlive = false;
	}

	if (hector->IsColliding())
	{
		if (hectorAttacking && eirikaAlive)
			eirikaAlive = false;
	}
}

void Program::Draw()
{
	if (eirikaAlive)
		eirika->Draw();

	if (hectorAlive)
		hector->Draw();

	eirika->Draw();
	hector->Draw();
}
