#include "Program.h"
#include "Textures/Importer/TextureImporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Quaternion.h"
#include "Collisions/CollisionManager.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	camera = new FirstPersonController(Vector3(0, 0, 0), mainCamera, rendererInstance);

	background = new Sprite("res/textures/Background.jpg", Vector3(0, 30.0f, -60.0f), Vector3(), -width, -height, rendererInstance);
	ground = new Sprite("res/textures/Background.jpg", Vector3(0, -30.0f, 15.0f), Vector3(90.0f, 0, 0), -width, -height, rendererInstance);
	cube = new Mesh("res/textures/sans-dance.jpg", Vector3(), Vector3(), 32, 32, rendererInstance);
}

Program::~Program()
{
	delete background;
	delete ground;
	delete camera;
	delete cube;
}

void Program::Update()
{
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
	ground->Draw();
	cube->Draw();
}
