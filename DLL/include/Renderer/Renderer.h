#pragma once

#include <vector>
#include <string>
#include "Utilities/Vector2.h"
#include "Utilities/MY4X4.h"
#include "Utilities/Transform.h"
#include "Utilities/Exporter.h"
#include "Utilities/Material.h"

#include "glm.hpp"
#include "Camera/Camera.h"
#include "Lightning/LightManager.h"
#include "Vertex.h"

using namespace std;

SIRENITO_API class Renderer
{
private:
	glm::mat4 projection;
	Camera* mainCamera;
	LightManager* lightManager;
	float width;
	float height;

public:
	unsigned int basicShaderProgram;
	unsigned int textureShaderProgram;

	SIRENITO_API Renderer(float screenWidth, float screenHeight, bool hasPerspective, Camera* camera, LightManager* light);
	SIRENITO_API void Clear();

	SIRENITO_API unsigned int CreateBuffer();
	SIRENITO_API unsigned int CreateVertexArray();
	SIRENITO_API void SetData(Transform* transform, Material material, bool hasTexture, float* positions, int positionsSize, unsigned int* indices, float indicesSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	SIRENITO_API void SetData(Transform* transform, Material material, bool hasTexture, vector<Vertex> vertices, vector<unsigned int> indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	SIRENITO_API void AddVertices(Vector2 vertices[], int vertexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty);
	SIRENITO_API void DrawWire(unsigned int& VAO, int indexQty);
	SIRENITO_API void Draw(unsigned int& VAO, int indexQty, unsigned int texture);
	SIRENITO_API glm::mat4 MVP_Transformation(MY4X4 model);
	SIRENITO_API glm::mat4 GetView();

	SIRENITO_API void CompileShader(string vertexSource, string fragmentSource, unsigned int* shaderProgram);

	SIRENITO_API void SetProjection(bool shouldBePerspective);

	SIRENITO_API void SetShaderBool(unsigned int shader, const char* name, bool value) const;
	SIRENITO_API void SetShaderInt(unsigned int shader, const char* name, int value) const;
	SIRENITO_API void SetShaderFloat(unsigned int shader, const char* name, float value) const;
	SIRENITO_API void SetShaderVector2(unsigned int shader, const char* name, Vector2  value) const;
	SIRENITO_API void SetShaderVector3(unsigned int shader, const char* name, Vector3  value) const;
	SIRENITO_API void SetShaderVector4(unsigned int shader, const char* name, Vector4 value) const;
	SIRENITO_API void SetShaderMatrix(unsigned int shader, const char* name, MY4X4 value) const;
	SIRENITO_API void SetShaderMatrix(unsigned int shader, const char* name, glm::mat4 value) const;

};