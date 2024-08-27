#pragma once

#include <vector>
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"

using namespace std;

SIRENITO_API class Renderer
{
private:
	unsigned int buffer;
	//vector<float> verticesToDraw;

	unsigned int shaderProgram;
public:

	SIRENITO_API void Clear();

	SIRENITO_API void CreateBuffer();
	SIRENITO_API unsigned int* GetBuffer();
	SIRENITO_API void SetData(float positions[], int arraySize);

	SIRENITO_API void AddVertices(Vector2f vertices[], int vertexQty);
	SIRENITO_API void Draw();

	SIRENITO_API void CompileBasicShader();
};
