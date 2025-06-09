#include "Program.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	lightManager->SetPointLight(new PointLight(Color(1.0f, 0.3f, 0.8f, 1.0f), Vector3(2.0f, 0.5f, 0.0f)));
	lightManager->SetSpotLight(new SpotLight(Color(0.5f, 0.7f, 0.5f, 1.0f), Vector3(-5.0f, 3.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 6.0f, 7.5f));
	lightManager->SetDirectionalLight(new DirectionalLight(Color(0.4f, 0.4f, 0.4f, 1.0f), Vector3(0.0f, -1.0f, -1.0f)));

	firstPersonCamera = new FirstPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	thirdPersonCamera = new ThirdPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	isFirstPerson = true;

	background = new Sprite("res/textures/Background.jpg", Vector3(0, 30.0f, -30.0f), Vector3(), -width, -height, rendererInstance);
	ground = new Sprite("res/textures/Background.jpg", Vector3(0, -2.0f, 0.0f), Vector3(90.0f, 0, 0), 10.0f, 10.0f, rendererInstance);
	//"res/textures/sans-dance.jpg",
	cube = new Mesh(Vector3(0.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);
	cube2 = new Mesh(Vector3(-5.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);

}

Program::~Program()
{
	delete background;
	delete ground;
	delete firstPersonCamera;
	delete thirdPersonCamera;
	delete cube;
	delete cube2;
}

void Program::Update()
{
	lightManager->GetPointLight()->transform.RotateAround(Vector3(), Vector3::Up(), pointLightRotationSpeed);


	if (isFirstPerson)
		firstPersonCamera->Update(inputInstance);
	else
		thirdPersonCamera->Update(inputInstance);

	if (inputInstance->isKeyDown(Keys::F2))
	{
		hasPerspective = !hasPerspective;
		rendererInstance->SetProjection(hasPerspective);
	}

	if (inputInstance->isKeyDown(Keys::N1))
		isFirstPerson = true;
	if (inputInstance->isKeyDown(Keys::N3))
	{
		thirdPersonCamera->SetThirdPerson(Vector3(0, 2.5f, -10));
		isFirstPerson = false;
	}
}

void Program::Draw()
{
	background->Draw();
	ground->Draw();
	cube->Draw();
	cube2->Draw();
	if (!isFirstPerson)
		thirdPersonCamera->mesh->Draw();
}
