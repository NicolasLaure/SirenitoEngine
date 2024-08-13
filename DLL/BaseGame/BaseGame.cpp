#include "BaseGame.h"

#include "GLFW/glfw3.h"
#include "Window/Window.h"

void BaseGame::RunProgram(int width, int height, const char* title)
{
	if (!glfwInit())
		return;

	Window windowInstance = Window(width, height, title);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}
