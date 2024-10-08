#pragma once

#include "GLFW/glfw3.h"
#include "Utilities/Exporter.h"

SIRENITO_API class Window
{
private:
	GLFWwindow* window = nullptr;

public:
	SIRENITO_API Window(int width, int height, const char* title);

	SIRENITO_API GLFWwindow* GetWindow();

	SIRENITO_API bool IsWindowOpen();
};
