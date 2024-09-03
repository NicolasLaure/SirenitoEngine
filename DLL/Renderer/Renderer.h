#pragma once

#include <vector>
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"
#include "ShapeBufferStruct.h"

using namespace std;

SIRENITO_API class Renderer
{
private:
	//vector<float> verticesToDraw;

public:
	ShapeBuffer shapeBuffer;
	unsigned int shaderProgram;

	SIRENITO_API void Clear();

	SIRENITO_API void CreateBuffer();
	SIRENITO_API unsigned int* GetBuffer();
	SIRENITO_API void SetData(float* positions, int positionsSize, unsigned int* indices, float indicesSize);

	SIRENITO_API void AddVertices(Vector2f vertices[], int vertexQty);
	SIRENITO_API void Draw();

	SIRENITO_API void CompileBasicShader();
};
