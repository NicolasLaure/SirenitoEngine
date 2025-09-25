#include "Program.h"

Program::Program(int width, int height, const char* title) : BaseGame(width, height, title)
{
	rendererInstance->SetProjection(hasPerspective);

	lightManager->SetPointLight(new PointLight(Color(1.0f, 0.3f, 0.8f, 1.0f), Vector3(2.0f, 0.5f, 0.0f)));
	lightManager->SetSpotLight(new SpotLight(Color(0.5f, 0.7f, 0.5f, 1.0f), Vector3(-5.0f, 3.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), 6.0f, 7.5f));
	lightManager->SetDirectionalLight(new DirectionalLight(Color(0.4f, 0.4f, 0.4f, 1.0f), Vector3(0.0f, -1.0f, -1.0f)));

	firstPersonCamera = new FirstPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	thirdPersonCamera = new ThirdPersonController(Vector3(0, 1, 0), mainCamera, rendererInstance);
	isFirstPerson = true;
	firstPersonCamera->SetFirstPerson();

	background = new Sprite("res/textures/Background.jpg", Vector3(0, 30.0f, -30.0f), Vector3(), -width, -height, rendererInstance);
	ground = new Sprite("res/textures/Background.jpg", Vector3(0, -2.0f, 0.0f), Vector3(90.0f, 0, 0), 100.0f, 100.0f, rendererInstance);
	cube = new Cube(Vector3(0.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);
	cube2 = new Cube(Vector3(-5.0f, 0.0f, 0.0f), Vector3(), Material(Color(1.0f, 0.6f, 0.3f, 1.0f), 1.0f), rendererInstance);

	//mclarenmodel = new Model("res/models/MclarenF1Frame.fbx", Material(), rendererInstance);
	//mclarenmodel->transform->SetLocalScale(Vector3(0.01f, 0.01f, 0.01f));
	//mclarenmodel->transform->SetPositionAndRotation(Vector3(5.0f, 0.0f, 0.0f), Quaternion::Euler(0.0f, 0.0f, 0.0f));

	//backpackModel = new Model("res/models/backpack/backpack.obj", Material(), rendererInstance);
	//tank = new Tank("res/models/Tank/Tank.fbx", Vector3(0.0f, -1.5f, -0.0f), rendererInstance);
	scene = new Scene("res/models/BSP_Scene/BSP_Scene.fbx", rendererInstance);
	tank = new Tank(scene->GetModel("Hull"));
}

Program::~Program()
{
	delete background;
	delete ground;
	delete firstPersonCamera;
	delete thirdPersonCamera;
	delete cube;
	delete cube2;
	//delete mclarenmodel;
	//delete backpackModel;
	delete tank;
	delete scene;
}

void Program::Update()
{
	lightManager->GetPointLight()->transform.RotateAround(Vector3(), Vector3::Up(), pointLightRotationSpeed);

	if (inputInstance->isKeyDown(Keys::DELETE))
	{
		delete tank;
		tank = nullptr;
	}

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

	if (tank != nullptr)
		tank->Update(inputInstance);

}

void Program::Draw()
{
	background->Draw();
	ground->Draw();
	//cube->Draw();
	//cube2->Draw();
	//mclarenmodel->Draw();
	//backpackModel->Draw();
	if (tank != nullptr)
		tank->Draw();

	if (scene != nullptr)
		scene->Draw();

	if (!isFirstPerson)
		thirdPersonCamera->mesh->Draw();
}
