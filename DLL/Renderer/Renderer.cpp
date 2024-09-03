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
	glGenBuffers(1, &shapeBuffer.VBO);
	glGenBuffers(1, &shapeBuffer.EBO);
}

unsigned int* Renderer::GetBuffer()
{
	return &shapeBuffer.VBO;
}

void Renderer::SetData(float* positions, int positionsSize, unsigned int* indices, float indicesSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, shapeBuffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, positionsSize * sizeof(float), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBuffer.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glUseProgram(shaderProgram);
}

void Renderer::AddVertices(Vector2f vertices[], int vertexQty)
{
	/*for (int i = 0; i < vertexQty; i++)
	{
		verticesToDraw.push_back(vertices[i].x);
		verticesToDraw.push_back(vertices[i].y);
	}*/
}

void Renderer::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBuffer.EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::CompileBasicShader()
{
	unsigned int vertexShader;
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
