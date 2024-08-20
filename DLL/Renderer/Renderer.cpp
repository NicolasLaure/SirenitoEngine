#include "Renderer.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <algorithm>

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

void Renderer::AddVertices(Vector2f vertices[], int vertexQty)
{
	for (int i = 0; i < vertexQty; i++)
	{
		verticesToDraw.push_back(vertices[i].x);
		verticesToDraw.push_back(vertices[i].y);
	}
}

void Renderer::Draw()
{
	float* vertices = new float[verticesToDraw.size()];

	copy(verticesToDraw.begin(), verticesToDraw.end(), vertices);
	SetData(vertices, verticesToDraw.size());

	glBegin(GL_TRIANGLES);
	glDrawArrays(GL_TRIANGLES, 0, verticesToDraw.size() / 2);
	glEnd();
}
