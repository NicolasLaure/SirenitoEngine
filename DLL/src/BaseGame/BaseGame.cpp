#include "BaseGame/BaseGame.h"

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
	rendererInstance = new Renderer(width, height, hasPerspective, mainCamera);
	inputInstance = new Input(windowInstance);

	FileReader fileReader;
	const char* basicVertexPath = "res/shaders/BasicVertex.txt";
	const char* basicFragmentPath = "res/shaders/BasicFragment.txt";

	string basicVertexSource = fileReader.ParseText(basicVertexPath);
	string basicFragmentSource = fileReader.ParseText(basicFragmentPath);

	rendererInstance->CompileShader(basicVertexSource, basicFragmentSource, &rendererInstance->basicShaderProgram);

	const char* textureVertexPath = "res/shaders/vertex_texture.txt";
	const char* textureFragmentPath = "res/shaders/fragment_texture.txt";

	string textureVertexSource = fileReader.ParseText(textureVertexPath);
	string textureFragmentSource = fileReader.ParseText(textureFragmentPath);

	rendererInstance->CompileShader(textureVertexSource, textureFragmentSource, &rendererInstance->textureShaderProgram);
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

		inputInstance->UpdateInput();
		Update();
		/* Render all loaded 2D entities */
		Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance->GetWindow());
	}

	delete mainCamera;
	delete windowInstance;
	delete rendererInstance;
	delete inputInstance;
	glfwTerminate();
	return;
}

void BaseGame::Update()
{
}

void BaseGame::Draw()
{
}
