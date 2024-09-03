#include "BaseGame.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Entity/Entity2D/Shape/Shape.h"

void BaseGame::RunProgram(int width, int height, const char* title)
{
	/* Initialize the glfw library */
	if (!glfwInit())
		return;

	Window windowInstance = Window(width, height, title);
	Renderer rendererInstance = Renderer();

	glewInit();

	rendererInstance.CompileBasicShader();

	float vertices[12] =
	{
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[6] =
	{
		0, 1, 3,
		1, 2, 3
	};

	float vertices2[12] =
	{
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	0.0f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
	};

	Shape rectangle2 = Shape(vertices2, 12, indices, 6, &rendererInstance);
	Shape rectangle = Shape(vertices, 12, indices, 6, &rendererInstance);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		rectangle.Draw();
		rectangle2.Draw();
		/* Render all loaded 2D entities */
		//rendererInstance.Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}
