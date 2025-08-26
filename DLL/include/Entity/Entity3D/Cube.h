#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Mesh.h"
#include "Textures/Texture.h"
#include "Textures/Importer/TextureImporter.h"
#include <vector>

using namespace std;

SIRENITO_API class Cube : public Mesh
{
protected:
	SIRENITO_API void Init(Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance);
	SIRENITO_API void Init(const char* texturePath, Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance);
	SIRENITO_API vector<Vertex> GetVertices();
	SIRENITO_API vector<Vertex> GetVertices(Vector2 minCoords, Vector2 maxCoords);
	SIRENITO_API vector<unsigned int> GetIndices();
public:

	SIRENITO_API Cube(Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance);
	SIRENITO_API Cube(const char* texturePath, Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance);
	SIRENITO_API Cube(const char* texturePath, Vector3 position, Vector3 eulers, Renderer* rendererInstance);
	SIRENITO_API Cube(const char* texturePath, Material material, Renderer* rendererInstance);
	SIRENITO_API Cube(const char* texturePath, Renderer* rendererInstance);
	SIRENITO_API ~Cube();

	SIRENITO_API void SetTexture(const char* path);
};