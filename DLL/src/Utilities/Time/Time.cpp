#include "Utilities/Time/Time.h"
#include "GLFW/glfw3.h"

float Time::GetTime()
{
	return (float)glfwGetTime();
}
