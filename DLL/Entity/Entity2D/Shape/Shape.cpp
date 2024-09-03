#include "Shape.h"

Shape::Shape(float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->vertices = vertices;
	this->rendererInstance = rendererInstance;
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
	rendererInstance->SetData(vertices, vertexQty, indices, indexQty, VBO, EBO);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->Draw(EBO, VBO);
}
