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

Vector2 Window::GetWindowSize()
{
	int width = 0;
	int height = 0;
	glfwGetWindowSize(window, &width, &height);
	return Vector2(width, height);
}
