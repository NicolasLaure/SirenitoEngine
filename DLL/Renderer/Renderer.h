#pragma once

#include <vector>
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"

using namespace std;

SIRENITO_API class Renderer
{
private:
	//vector<float> verticesToDraw;

public:
	unsigned int shaderProgram;

	SIRENITO_API void Clear();

	SIRENITO_API unsigned int CreateBuffer();
	SIRENITO_API void SetData(float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VBO, unsigned int& EBO);

	SIRENITO_API void AddVertices(Vector2f vertices[], int vertexQty);
	SIRENITO_API void Draw(unsigned int& EBO, unsigned int& VBO);

	SIRENITO_API void CompileBasicShader();
};
