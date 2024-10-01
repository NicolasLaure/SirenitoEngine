#include "Input.h"

Input::Input(GLFWwindow* window)
{
	this->window = window;
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

Input::~Input()
{
}


void Input::UpdateInput()
{
	glfwPollEvents();
}

bool Input::isKeyDown(Keys key)
{
	return glfwGetKey(window, (int)key) == GLFW_PRESS;
}

bool Input::isKeyPressed(Keys key)
{
	return glfwGetKey(window, (int)key) == GLFW_REPEAT;
}

bool Input::isKeyUp(Keys key)
{
	return glfwGetKey(window, (int)key) == GLFW_RELEASE;
}
