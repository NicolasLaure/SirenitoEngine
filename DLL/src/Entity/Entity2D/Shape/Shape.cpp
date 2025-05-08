#include "Entity/Entity2D/Shape/Shape.h"

Shape::Shape(Vector3 position, Vector3 eulers, Color color, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->indexQty = indexQty;
	this->vertices = vertices;
	this->indices = indices;
	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
	transform = new Transform();
	transform->SetPositionAndRotation(position, Quaternion::Euler(eulers));

	rendererInstance->SetData(transform, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

Shape::Shape(Color color, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
{
	this->vertexQty = vertexQty;
	this->indexQty = indexQty;
	this->vertices = vertices;
	this->indices = indices;
	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
}

Shape::~Shape()
{
	delete transform;

	delete[] vertices;
	delete[] indices;
}

void Shape::Draw()
{
	rendererInstance->SetData(transform, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, indexQty);
}

void Shape::DrawWire()
{
	rendererInstance->SetData(transform, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
	rendererInstance->DrawWire(VAO, indexQty);
}
