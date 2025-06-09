#include "Renderer/Renderer.h"

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <algorithm>
#include "gtc/matrix_transform.hpp"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::Renderer(float screenWidth, float screenHeight, bool hasPerspective, Camera* camera, LightManager* light)
{
	glewInit();
	width = screenWidth;
	height = screenHeight;
	SetProjection(hasPerspective);

	mainCamera = camera;
	this->lightManager = light;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_SAMPLE_ALPHA_TO_ONE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND); //Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	/*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);*/
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

void Renderer::SetData(Transform* transform, Material material, bool hasTexture, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	MY4X4 model = transform->LocalToWorldMatrix();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, positionsSize * sizeof(float), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	if (!hasTexture)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 7));
		glEnableVertexAttribArray(2);
	}
	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 7));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)(sizeof(float) * 9));
		glEnableVertexAttribArray(3);
	}

	unsigned int shaderProgram = basicShaderProgram;

	if (hasTexture)
		shaderProgram = textureShaderProgram;

	//Setting MVP Uniforms
	SetShaderMatrix(shaderProgram, "u_Model", model);
	SetShaderMatrix(shaderProgram, "u_View", GetView());
	SetShaderMatrix(shaderProgram, "u_Projection", projection);

	//Setting Tint Color
	SetShaderVector4(shaderProgram, "u_Tint", Vector4(material.tint.r, material.tint.g, material.tint.b, material.tint.a));
	//Setting Glossiness
	SetShaderFloat(shaderProgram, "u_ObjectGlossiness", material.glossiness);

	//SettingAmbientLight
	GlobalLight* ambientLight = lightManager->GetAmbientLight();
	Vector3 lightColor = ambientLight == nullptr ? Vector3(0.0f, 0.0f, 0.0f) : Vector3(ambientLight->color.r, ambientLight->color.g, ambientLight->color.b);
	SetShaderVector3(shaderProgram, "u_AmbientLightColor", lightColor);

	PointLight* pointLight = lightManager->GetPointLight();
	if (pointLight != nullptr)
	{
		SetShaderVector3(shaderProgram, "u_PointLight.color", Vector3(pointLight->color.r, pointLight->color.g, pointLight->color.b));
		SetShaderVector3(shaderProgram, "u_PointLight.position", pointLight->transform.GetPosition());
		SetShaderFloat(shaderProgram, "u_PointLight.constant", 1.0f);
		SetShaderFloat(shaderProgram, "u_PointLight.linear", 0.22f);
		SetShaderFloat(shaderProgram, "u_PointLight.quadratic", 0.2f);
	}

	DirectionalLight* directionalLight = lightManager->GetDirectionalLight();
	if (directionalLight != nullptr)
	{
		SetShaderVector3(shaderProgram, "u_DirectionalLight.color", Vector3(directionalLight->color.r, directionalLight->color.g, directionalLight->color.b));
		SetShaderVector3(shaderProgram, "u_DirectionalLight.direction", directionalLight->GetDirection());
	}

	SetShaderVector3(shaderProgram, "u_ViewPos", mainCamera->view->GetPosition());
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

glm::mat4 Renderer::MVP_Transformation(MY4X4 model)
{
	return projection * GetView() * model.ToGlm();
}

glm::mat4 Renderer::GetView()
{
	return glm::lookAt(mainCamera->view->GetPosition().ToGlm(), (mainCamera->view->GetPosition() + mainCamera->view->GetForward()).ToGlm(), mainCamera->view->GetUp().ToGlm());
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

void Renderer::SetShaderBool(unsigned int shader, const char* name, bool value) const
{
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, name), (int)value);
}

void Renderer::SetShaderInt(unsigned int shader, const char* name, int value) const
{
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, name), value);
}

void Renderer::SetShaderFloat(unsigned int shader, const char* name, float value) const
{
	glUseProgram(shader);
	glUniform1f(glGetUniformLocation(shader, name), value);
}

void Renderer::SetShaderVector2(unsigned int shader, const char* name, Vector2 value) const
{
	glUseProgram(shader);
	glm::vec2 vec2 = value.ToGlm();
	glUniform2fv(glGetUniformLocation(shader, name), 1, &vec2[0]);
}

void Renderer::SetShaderVector3(unsigned int shader, const char* name, Vector3 value) const
{
	glUseProgram(shader);
	glm::vec3 vec3 = value.ToGlm();
	glUniform3fv(glGetUniformLocation(shader, name), 1, &vec3[0]);
}

void Renderer::SetShaderVector4(unsigned int shader, const char* name, Vector4 value) const
{
	glUseProgram(shader);
	glm::vec4 vec4 = value.ToGlm();
	glUniform4fv(glGetUniformLocation(shader, name), 1, &vec4[0]);
}

void Renderer::SetShaderMatrix(unsigned int shader, const char* name, MY4X4 value) const
{
	glUseProgram(shader);
	glm::mat4 mvp = value.ToGlm();
	glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &mvp[0][0]);
}
void Renderer::SetShaderMatrix(unsigned int shader, const char* name, glm::mat4 value) const
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_FALSE, &value[0][0]);
}
