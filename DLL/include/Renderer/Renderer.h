#pragma once

#include <vector>
#include <string>
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"
#include "Utilities/Color.h"

#include "glm.hpp"
#include "Camera/Camera.h"

using namespace std;

SIRENITO_API class Renderer
{
private:
	glm::mat4 projection;
	Camera* mainCamera;
	float width;
	float height;

public:
	unsigned int basicShaderProgram;
	unsigned int textureShaderProgram;

	SIRENITO_API Renderer(float screenWidth, float screenHeight, bool hasPerspective, Camera* camera);

	SIRENITO_API void Clear();

	SIRENITO_API unsigned int CreateBuffer();
	SIRENITO_API unsigned int CreateVertexArray();
	SIRENITO_API void SetData(glm::mat4 model, Color color, bool hasTexture, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	SIRENITO_API void AddVertices(Vector2f vertices[], int vertexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty);
	SIRENITO_API void DrawWire(unsigned int& VAO, int indexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty, unsigned int texture);
	SIRENITO_API glm::mat4 MVP_Transformation(glm::mat4 model);

	SIRENITO_API void CompileShader(string vertexSource, string fragmentSource, unsigned int* shaderProgram);

	SIRENITO_API void SetProjection(bool shouldBePerspective);
};