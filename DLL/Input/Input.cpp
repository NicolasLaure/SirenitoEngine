#include "Input.h"

Input::Input(GLFWwindow* window)
{
	this->window = window;
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GLFW_FALSE);
}

Input::~Input()
{
}

void Input::ClearReleasedKeys()
{
	List<Keys> keysToRemove;

	for (int i = 0; i < pressedKeys.GetCount(); i++)
	{
		if (isKeyUp(pressedKeys.GetValueAt(i)))
			keysToRemove.PushBack(pressedKeys.GetValueAt(i));
	}

	for (int i = 0; i < keysToRemove.GetCount(); i++)
	{
		pressedKeys.Remove(keysToRemove.GetValueAt(i));
	}
}

void Input::UpdateInput()
{
	glfwPollEvents();
	ClearReleasedKeys();
}

bool Input::isKeyDown(Keys key)
{
	if (glfwGetKey(window, (int)key) == GLFW_PRESS)
	{
		for (int i = 0; i < pressedKeys.GetCount(); i++)
		{
			if (pressedKeys.Contains(key))
				return false;
		}
		pressedKeys.PushBack(key);
		return true;
	}
}

bool Input::isKeyPressed(Keys key)
{
	int keyChecked = glfwGetKey(window, (int)key);
	return keyChecked == GLFW_PRESS || keyChecked == GLFW_REPEAT;
}

bool Input::isKeyUp(Keys key)
{
	int keyChecked = glfwGetKey(window, (int)key);
	return keyChecked == GLFW_RELEASE;
}
