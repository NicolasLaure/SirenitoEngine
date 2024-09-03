#include "Shape.h"

Shape::Shape(float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->indexQty = indexQty;
	this->vertices = vertices;
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
	rendererInstance->SetData(vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->Draw(VAO, indexQty);
}
