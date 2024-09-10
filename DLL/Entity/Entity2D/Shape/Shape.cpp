#include "Shape.h"

Shape::Shape(glm::vec3 position, glm::vec3 eulers, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->indexQty = indexQty;
	this->vertices = vertices;
	this->indices = indices;
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	SetPosition(position);
	SetRotation(eulers);
	SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->SetData(trs, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, indexQty);
}
