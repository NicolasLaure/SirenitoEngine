#include "Shape.h"

Shape::Shape(glm::vec3 position, glm::vec3 eulers, Color color, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance)
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

	SetPosition(position);
	SetRotation(eulers);
	SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
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
	delete[] vertices;
	delete[] indices;
}

void Shape::Draw()
{
	rendererInstance->SetData(trs, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, indexQty);
}
