#pragma once
#include "Utilities/Exporter.h"
#include <vector>
#include "Entity/Entity3D/Entity3D.h"
#include "Renderer/Vertex.h"
#include "Textures/Texture.h"

using namespace std;

SIRENITO_API class Mesh : public Entity3D
{
protected:
	Material material;
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	SIRENITO_API Mesh();
	SIRENITO_API Mesh(const char* name, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Material material, Renderer* rendererInstance);
	SIRENITO_API Mesh(const char* name, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Material material);
	SIRENITO_API ~Mesh();
	SIRENITO_API void Draw();
	SIRENITO_API void DrawWire();
	SIRENITO_API void SetRendererInstance(Renderer* instance);
};