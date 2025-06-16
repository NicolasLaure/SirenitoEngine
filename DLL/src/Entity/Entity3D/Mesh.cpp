#include "Entity/Entity3D/Mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Texture* texture, Material material, Renderer* rendererInstance)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;
	this->material = material;
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
}

Mesh::~Mesh()
{
	if (texture != nullptr)
		delete texture;
}

void Mesh::Draw()
{
	if (texture != nullptr)
	{
		rendererInstance->SetData(transform, material, true, vertices, indices, VAO, VBO, EBO);
		rendererInstance->Draw(VAO, vertices.size(), texture->GetId());
		return;
	}

	rendererInstance->SetData(transform, material, false, vertices, indices, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, vertices.size());
}
