#include "Triangle.h"

Triangle::Triangle(glm::vec3 position, float width, float height, Renderer* renderer) : Shape(GetVertices(width, height), 9, GetIndices(), 3, renderer)
{
	SetPosition(position);
	SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

float* Triangle::GetVertices(float width, float height)
{
	return new float[9]
		{
			-width / 2, -height / 2, 0.0f,
			 width / 2, -height / 2, 0.0f,
			 0.0f, height / 2, 0.0f,
		};;
}

unsigned int* Triangle::GetIndices()
{
	return new unsigned int[3]
		{
			0, 1, 2,
		};
}