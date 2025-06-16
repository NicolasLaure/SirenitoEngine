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
	Texture* texture = nullptr;
	Material material;
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	SIRENITO_API Mesh();
	SIRENITO_API Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture* texture, Material material, Renderer* rendererInstance);
	SIRENITO_API ~Mesh();
	SIRENITO_API void Draw();
};