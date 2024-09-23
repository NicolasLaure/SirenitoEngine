#include "Rectangle.h"

Rectangle::Rectangle(glm::vec3 position, float width, float height, Renderer* renderer) : Shape(GetVertices(width, height), 12, GetIndices(), 6, renderer)
{
	SetPosition(position);
	SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

float* Rectangle::GetVertices(float width, float height)
{
	return new float[12]
		{
			width / 2, -height / 2, 0.0f,
				width / 2, height / 2, 0.0f,
				-width / 2, height / 2, 0.0f,
				-width / 2, -height / 2, 0.0f
		};;
}

unsigned int* Rectangle::GetIndices()
{
	return new unsigned int[6]
		{
			0, 1, 3,
				1, 2, 3
		};;
}
