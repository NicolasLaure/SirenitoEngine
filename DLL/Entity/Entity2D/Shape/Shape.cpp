#include "Shape.h"


Shape::Shape(float vertices[], int vertexQty, Renderer rendererInstance)
{
	this->vertexQty = vertexQty;
	this->vertices = vertices;
	rendererInstance.SetData(vertices, vertexQty);
}

Shape::~Shape()
{
	delete[] vertices;
}

void Shape::Draw(Renderer rendererInstance)
{
	rendererInstance.Draw();
	//rendererInstance.AddVertices(vertices, vertexQty);
}
