#include "Shape.h"

Shape::Shape(glm::mat4 model, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->indexQty = indexQty;
	this->vertices = vertices;
	this->indices = indices;
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	this->model = model;

	rendererInstance->SetData(this->model, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->SetData(this->model, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, indexQty);
}
