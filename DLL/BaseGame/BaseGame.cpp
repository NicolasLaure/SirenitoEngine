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

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(windowInstance.GetWindow()))
	{
		/* Render here */
		rendererInstance.Clear();

		glBegin(GL_TRIANGLES);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glColor3f(1, 0, 0);
		//glVertex2f(-0.5, -0.5);

		//glColor3f(0, 1, 0);
		//glVertex2f(0, 0.5);

		//glColor3f(0, 0, 1);
		//glVertex2f(0.5, -0.5);
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(windowInstance.GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return;
}
