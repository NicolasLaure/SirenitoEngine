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

	glewInit();

	Window windowInstance = Window(width, height, title);
	Renderer rendererInstance;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);

		glVertex2f(-0.2f, 0.0f);
		glVertex2f(0.2f, 0.0f);
		glVertex2f(0.0f, 0.8f);

		glVertex2f(0.4f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(-0.2f, -0.65f);

		glVertex2f(-0.4f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(-0.05f, -0.375f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);

		glVertex2f(-0.2f, 0.0f);
		glVertex2f(0.05f, 0.0f);
		glVertex2f(0.13f, -0.3f);

		glVertex2f(-0.05f, 0.0f);
		glVertex2f(0.2f, 0.0f);
		glVertex2f(-0.13f, -0.3f);

		glVertex2f(-0.05f, 0.0f);
		glVertex2f(0.05f, 0.0f);
		glVertex2f(0, 0.2f);

		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}
