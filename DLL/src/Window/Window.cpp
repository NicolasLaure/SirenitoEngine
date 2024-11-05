#include "Window/Window.h"

Window::Window(int width, int height, const char* title)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!IsWindowOpen())
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

bool Window::IsWindowOpen()
{
	return window;
}
