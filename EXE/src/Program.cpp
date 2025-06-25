#include "Program.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	lightManager->SetPointLight(new PointLight(Color(1.0f, 0.3f, 0.8f, 1.0f), Vector3(2.0f, 0.5f, 0.0f)));
	lightManager->SetSpotLight(new SpotLight(Color(0.5f, 0.7f, 0.5f, 1.0f), Vector3(-5.0f, 3.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 6.0f, 7.5f));
	lightManager->SetDirectionalLight(new DirectionalLight(Color(0.4f, 0.4f, 0.4f, 1.0f), Vector3(0.0f, -1.0f, -1.0f)));

	firstPersonCamera = new FirstPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	thirdPersonCamera = new ThirdPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	isFirstPerson = true;
	firstPersonCamera->SetFirstPerson();

	background = new Sprite("res/textures/Background.jpg", Vector3(0, 30.0f, -30.0f), Vector3(), -width, -height, rendererInstance);
	ground = new Sprite("res/textures/Background.jpg", Vector3(0, -2.0f, 0.0f), Vector3(90.0f, 0, 0), 10.0f, 10.0f, rendererInstance);
	//"res/textures/sans-dance.jpg",
	cube = new Cube(Vector3(0.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);
	cube2 = new Cube(Vector3(-5.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);

	mclarenmodel = new Model("res/models/MclarenF1Frame.fbx", Material(), rendererInstance);
	mclarenmodel->transform->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
	mclarenmodel->transform->SetPositionAndRotation(Vector3(5.0f, 0.0f, 0.0f), Quaternion::Euler(90.0f, 0.0f, 0.0f));

	backpackModel = new Model("res/models/backpack/backpack.obj", Material(), rendererInstance);

	fw190model = new Model("res/models/Fw190/FW190.fbx", Material(), rendererInstance);
	fw190model->transform->SetLocalScale(Vector3(0.25f, 0.25f, 0.25f));
	fw190model->transform->SetPositionAndRotation(Vector3(0.0f, 0.0f, 5.0f), Quaternion::Euler(90.0f, 0.0f, 0.0f));
}

Program::~Program()
{
	delete background;
	delete ground;
	delete firstPersonCamera;
	delete thirdPersonCamera;
	delete cube;
	delete cube2;
	delete mclarenmodel;
	delete backpackModel;
	delete fw190model;
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
	{
		firstPersonCamera->SetFirstPerson();
		isFirstPerson = true;
	}
	if (inputInstance->isKeyDown(Keys::N3))
	{
		isFirstPerson = false;
		thirdPersonCamera->SetThirdPerson(Vector3(0, 2.5f, -10));
	}
}

void Program::Draw()
{
	background->Draw();
	ground->Draw();
	cube->Draw();
	cube2->Draw();
	mclarenmodel->Draw();
	backpackModel->Draw();
	fw190model->Draw();
	if (!isFirstPerson)
		thirdPersonCamera->mesh->Draw();
}
