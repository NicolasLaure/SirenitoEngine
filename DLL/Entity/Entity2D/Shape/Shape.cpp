#include "Shape.h"

Shape::Shape(float* vertices, int vertexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->vertices = vertices;
	this->rendererInstance = rendererInstance;
	rendererInstance->SetData(vertices, vertexQty);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw()
{
	rendererInstance->Draw();
}
