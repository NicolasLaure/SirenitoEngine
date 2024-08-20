#include "Renderer.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"

SIRENITO_API void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::CreateBuffer()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

unsigned int* Renderer::GetBuffer()
{
	return &buffer;
}

void Renderer::SetData(float positions[], int arraySize)
{
	glBufferData(GL_ARRAY_BUFFER, arraySize * sizeof(float), positions, GL_STATIC_DRAW);
}
