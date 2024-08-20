#include "BaseGame.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"

void BaseGame::RunProgram(int width, int height, const char* title)
{
	/* Initialize the glfw library */
	if (!glfwInit())
		return;

	Window windowInstance = Window(width, height, title);
	Renderer rendererInstance;

	glewInit();

	float positions[6] =
	{
		-0.5f,-0.5f,
		0.0f, 0.5f,
		0.5f,-0.5f
	};

	rendererInstance.CreateBuffer();
	rendererInstance.SetData(positions, 6);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		glBegin(GL_TRIANGLES);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}
