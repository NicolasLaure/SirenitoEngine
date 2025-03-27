#include "Input/Input.h"

Input::Input(Window* window)
{
	this->window = window;
	glfwSetInputMode(window->GetWindow(), GLFW_STICKY_KEYS, GLFW_FALSE);
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
	if (glfwGetKey(window->GetWindow(), (int)key) == GLFW_PRESS)
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
	int keyChecked = glfwGetKey(window->GetWindow(), (int)key);
	return keyChecked == GLFW_PRESS || keyChecked == GLFW_REPEAT;
}

bool Input::isKeyUp(Keys key)
{
	int keyChecked = glfwGetKey(window->GetWindow(), (int)key);
	return keyChecked == GLFW_RELEASE;
}

void Input::updateMouse()
{
	double xpos = 0;
	double ypos = 0;
	glfwGetCursorPos(window->GetWindow(), &xpos, &ypos);
	mouseDir = Vector2((float)xpos, (float)ypos);

	Vector2 windowSize = window->GetWindowSize();
	glfwSetCursorPos(window->GetWindow(), windowSize.x / 2, windowSize.y / 2);
}

Vector2 Input::GetMouseDir()
{
	return mouseDir;
}

