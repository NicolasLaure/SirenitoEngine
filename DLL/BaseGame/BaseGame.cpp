#include "BaseGame.h"

#include "Utilities/FileReader.h"

#include "gtc/matrix_transform.hpp"

#include <iostream>
#include <chrono>

BaseGame::BaseGame(int width, int height, const char* title)
{
	/* Initialize the glfw library */
	if (!glfwInit())
		return;


	windowInstance = new Window(width, height, title);
	mainCamera = new Camera();
	rendererInstance = new Renderer(width, height, mainCamera);

	FileReader fileReader;
	const char* vertexPath = "res/shaders/BasicVertex.txt";
	const char* fragmentPath = "res/shaders/BasicFragment.txt";

	string vertexSource = fileReader.ParseText(vertexPath);
	string fragmentSource = fileReader.ParseText(fragmentPath);

	rendererInstance->CompileBasicShader(vertexSource, fragmentSource);
}

void BaseGame::RunProgram()
{
	GLfloat currentTime = glfwGetTime();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance->GetWindow()))
	{
		/* Render here */
		rendererInstance->Clear();

		deltaTime = glfwGetTime() - currentTime;
		system("cls");
		std::cout << deltaTime;
		currentTime = glfwGetTime();

		Update();
		/* Render all loaded 2D entities */
		Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance->GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete mainCamera;
	delete windowInstance;
	delete rendererInstance;
	glfwTerminate();
	return;
}

void BaseGame::Update()
{
}

void BaseGame::Draw()
{
}
