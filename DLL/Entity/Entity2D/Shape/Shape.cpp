#include "Shape.h"

Shape::Shape(float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->vertices = vertices;
	this->rendererInstance = rendererInstance;
	rendererInstance->SetData(vertices, vertexQty, indices, indexQty);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->Draw();
}
