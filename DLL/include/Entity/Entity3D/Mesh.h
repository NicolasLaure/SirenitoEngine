#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Entity3D.h"
#include "Textures/Texture.h"
#include "Textures/Importer/TextureImporter.h"

SIRENITO_API class Mesh : public Entity3D
{
protected:
	Texture texture;
	Material material;


	SIRENITO_API void Init(Vector3 position, Vector3 eulers, Material color, Renderer* rendererInstance);
	SIRENITO_API void Init(const char* texturePath, Vector3 position, Vector3 eulers, Material color, Renderer* rendererInstance);
	SIRENITO_API float* GetVertices();
	SIRENITO_API float* GetVertices(Vector2 minCoords, Vector2 maxCoords);
	SIRENITO_API unsigned int* GetIndices();
public:

	SIRENITO_API Mesh(Vector3 position, Vector3 eulers, Material color, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, Vector3 position, Vector3 eulers, Material color, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, Vector3 position, Vector3 eulers, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, Material color, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* texturePath, Renderer* rendererInstance);
	SIRENITO_API ~Mesh();

	SIRENITO_API void SetTexture(const char* path);
	SIRENITO_API void Draw() override;
};