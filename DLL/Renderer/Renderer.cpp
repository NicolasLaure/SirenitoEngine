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
	glGenBuffers(1, &VBO);
}

unsigned int* Renderer::GetBuffer()
{
	return &VBO;
}

void Renderer::SetData(float* positions, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
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
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
