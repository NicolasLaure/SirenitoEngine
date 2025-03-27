#pragma once
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "KeysEnum.h"
#include "Utilities/Exporter.h"
#include "Utilities/List.h"
#include "Utilities/Vector2.h"

SIRENITO_API class Input
{
private:
	Window* window;
	List<Keys> pressedKeys;
	Vector2 mouseDir;

	SIRENITO_API void ClearReleasedKeys();
public:
	SIRENITO_API Input(Window* window);
	SIRENITO_API ~Input();

	SIRENITO_API void UpdateInput();
	SIRENITO_API bool isKeyDown(Keys key);
	SIRENITO_API bool isKeyPressed(Keys key);
	SIRENITO_API bool isKeyUp(Keys key);
	SIRENITO_API void updateMouse();
	SIRENITO_API Vector2 GetMouseDir();
};