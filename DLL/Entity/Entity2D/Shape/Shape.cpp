#include "Shape.h"


Shape::Shape(Vector2f vertices[], int vertexQty)
{
	this->vertexQty = vertexQty;
	this->vertices = vertices;
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw(Renderer rendererInstance)
{
	rendererInstance.AddVertices(vertices, vertexQty);
}
