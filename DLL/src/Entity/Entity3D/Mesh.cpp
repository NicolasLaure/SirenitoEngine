#include "Entity/Entity3D/Mesh.h"
#include <iostream>

void Mesh::SetRendererInstance(Renderer* instance)
{
	this->rendererInstance = instance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
}

Mesh::Mesh()
{
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Material material, Renderer* rendererInstance)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->material = material;
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Material material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->material = material;
	this->rendererInstance = nullptr;
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	if (textures.size() > 0)
	{
		rendererInstance->SetData(transform, material, true, vertices, indices, VAO, VBO, EBO);
		rendererInstance->Draw(VAO, vertices.size(), textures[0].GetId());
		return;
	}

	rendererInstance->SetData(transform, material, false, vertices, indices, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, vertices.size());
}
