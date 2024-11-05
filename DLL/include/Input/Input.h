#pragma once
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "KeysEnum.h"
#include "Utilities/Exporter.h"
#include "Utilities/List.h"

SIRENITO_API class Input
{
private:
	GLFWwindow* window;
	List<Keys> pressedKeys;

	SIRENITO_API void ClearReleasedKeys();
public:
	SIRENITO_API Input(GLFWwindow* window);
	SIRENITO_API ~Input();

	SIRENITO_API void UpdateInput();
	SIRENITO_API bool isKeyDown(Keys key);
	SIRENITO_API bool isKeyPressed(Keys key);
	SIRENITO_API bool isKeyUp(Keys key);
};