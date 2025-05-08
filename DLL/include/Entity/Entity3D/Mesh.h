#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Entity3D.h"
#include "Textures/Texture.h"
#include "Textures/Importer/TextureImporter.h"

SIRENITO_API class Mesh : public Entity3D
{
protected:
	float width;
	float height;
	Texture texture;
	Color color;


	SIRENITO_API void Init(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Color color, Renderer* rendererInstance);
	SIRENITO_API float* GetVertices(float width, float height);
	SIRENITO_API float* GetVertices(float width, float height, Vector2 minCoords, Vector2 maxCoords);
	SIRENITO_API unsigned int* GetIndices();
	SIRENITO_API void SetUVCoords(Vector2 minCoords, Vector2 maxCoords);
public:

	SIRENITO_API Mesh(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Color color, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, float width, float height, Color color, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, float width, float height, Renderer* rendererInstance);
	SIRENITO_API ~Mesh();

	SIRENITO_API void SetTexture(const char* path);
	SIRENITO_API void Draw() override;
};