#include "BaseGame.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Utilities/FileReader.h"

#include "gtc/matrix_transform.hpp"

#include <iostream>

BaseGame::BaseGame()
{

}

void BaseGame::RunProgram(int width, int height, const char* title)
{
	/* Initialize the glfw library */
	if (!glfwInit())
		return;

	Window windowInstance = Window(width, height, title);
	Camera mainCamera = Camera();
	Renderer rendererInstance = Renderer(width, height, &mainCamera);

	glewInit();

	FileReader fileReader;
	const char* vertexPath = "res/shaders/BasicVertex.txt";
	const char* fragmentPath = "res/shaders/BasicFragment.txt";

	string vertexSource = fileReader.ParseText(vertexPath);
	string fragmentSource = fileReader.ParseText(fragmentPath);

	rendererInstance.CompileBasicShader(vertexSource, fragmentSource);

	float vertices[12] =
	{
	 100.0f,  0.0f, 0.0f,
	 100.0f, 100.0f, 0.0f,
	0.0f, 100.0f, 0.0f,
	0.0f,  0.0f, 0.0f
	};

	unsigned int indices[6] =
	{
		0, 1, 3,
		1, 2, 3
	};

	float vertices2[12] =
	{
	width,  height - 100.0f, 0.0f,
	 width - 100.0f, height - 100.0f, 0.0f,
	width - 100.0f, height, 0.0f,
	width, height, 0.0f
	};

	mainCamera.Translate(glm::vec3(-25, 0, 0));

	glm::vec3 position = glm::vec3(100.0f, 50.0f, 0.0f);
	glm::vec3 eulers = glm::vec3(0.0f, 0.0f, 45.0f);

	rectangle = new Shape(position, eulers, vertices, 12, indices, 6, &rendererInstance);
	Shape rectangle2 = Shape(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), vertices2, 12, indices, 6, &rendererInstance);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		/*rectangle.Draw();
		rectangle2.Draw();*/

		Update();
		Draw();
		/* Render all loaded 2D entities */
		//rendererInstance.Draw();
		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete rectangle;
	glfwTerminate();
	return;
}

void BaseGame::Update()
{
}

void BaseGame::Draw()
{
}
