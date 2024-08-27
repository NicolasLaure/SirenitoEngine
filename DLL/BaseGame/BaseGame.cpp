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

	rendererInstance.CreateBuffer();
	rendererInstance.CompileBasicShader();

	float vertices[6] =
	{
		0.5f,-0.5f,
		0.0f, 0.5f,
		0.5f,-0.5f
	};

	Shape triangle = Shape(vertices, 6, rendererInstance);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		triangle.Draw(rendererInstance);

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
