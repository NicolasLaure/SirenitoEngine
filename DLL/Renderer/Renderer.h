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
	//vector<float> verticesToDraw;
	glm::mat4 projection;
	Camera* mainCamera;

public:
	unsigned int shaderProgram;

	SIRENITO_API Renderer(float screenWidth, float screenHeight, Camera* camera);

	SIRENITO_API void Clear();

	SIRENITO_API unsigned int CreateBuffer();
	SIRENITO_API unsigned int CreateVertexArray();
	SIRENITO_API void SetData(glm::mat4 model, Color color, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	SIRENITO_API void SetData(glm::mat4 model, Color color, unsigned int texture, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	SIRENITO_API void AddVertices(Vector2f vertices[], int vertexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty, unsigned int texture);
	SIRENITO_API glm::mat4 MVP_Transformation(glm::mat4 model);

	SIRENITO_API void CompileBasicShader(string vertexSource, string fragmentSource);
};