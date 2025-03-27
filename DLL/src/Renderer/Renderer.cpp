#include "Renderer/Renderer.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <algorithm>
#include "gtc/matrix_transform.hpp"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::Renderer(float screenWidth, float screenHeight, bool hasPerspective, Camera* camera)
{
	glewInit();
	width = screenWidth;
	height = screenHeight;
	SetProjection(hasPerspective);

	mainCamera = camera;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

unsigned int Renderer::CreateBuffer()
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	return buffer;
}
unsigned int Renderer::CreateVertexArray()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}

void Renderer::SetData(glm::mat4 model, Color color, bool hasTexture, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, positionsSize * sizeof(float), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	if (!hasTexture)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
	}
	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 7));
		glEnableVertexAttribArray(2);
	}

	unsigned int shaderProgram = basicShaderProgram;
	if (hasTexture)
		shaderProgram = textureShaderProgram;

	int mat4Uniform = glGetUniformLocation(shaderProgram, "u_MVP");
	glUseProgram(shaderProgram);
	glm::mat4 mvp = MVP_Transformation(model);
	glUniformMatrix4fv(mat4Uniform, 1, GL_FALSE, &mvp[0][0]);

	int colorUniform = glGetUniformLocation(shaderProgram, "u_Tint");
	glUseProgram(shaderProgram);
	glm::vec4 tintColor = glm::vec4(color.r, color.g, color.b, color.a);
	glUniform4fv(colorUniform, 1, &tintColor[0]);


}

void Renderer::AddVertices(Vector2 vertices[], int vertexQty)
{
	/*for (int i = 0; i < vertexQty; i++)
	{
		verticesToDraw.push_back(vertices[i].x);
		verticesToDraw.push_back(vertices[i].y);
	}*/
}

void Renderer::Draw(unsigned int& VAO, int indexQty)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, (void*)0);
}
void Renderer::DrawWire(unsigned int& VAO, int indexQty)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Draw(VAO, indexQty);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::Draw(unsigned int& VAO, int indexQty, unsigned int texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexQty, GL_UNSIGNED_INT, (void*)0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::mat4 Renderer::MVP_Transformation(glm::mat4 model)
{
	return projection * mainCamera->GetViewMatrix() * model;
}

void Renderer::CompileShader(string vertexSource, string fragmentSource, unsigned int* shaderProgram)
{
	unsigned int vertexShader;

	const char* vertexShaderSource = vertexSource.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;

	const char* fragmentShaderSource = fragmentSource.c_str();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	*shaderProgram = glCreateProgram();

	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Renderer::SetProjection(bool shouldBePerspective)
{
	if (!shouldBePerspective)
	{
		projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1000.0f);
		return;
	}
	projection = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 1000.0f);
}
