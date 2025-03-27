#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Shape/Shape.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"

SIRENITO_API class BaseGame
{
protected:
	bool hasPerspective = false;
public:
	float deltaTime = 0;
	Camera* mainCamera = nullptr;
	Window* windowInstance = nullptr;
	Renderer* rendererInstance = nullptr;
	Input* inputInstance = nullptr;

	SIRENITO_API BaseGame(int width, int height, const char* title);
	SIRENITO_API void RunProgram();
	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();
};