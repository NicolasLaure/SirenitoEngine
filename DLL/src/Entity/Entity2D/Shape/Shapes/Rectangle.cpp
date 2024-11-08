#include "Entity/Entity2D/Shape/Shapes/Rectangle.h"

Rectangle::Rectangle(Vector3 position, float width, float height, Color color, Renderer* renderer) : Shape(color, GetVertices(width, height), 28, GetIndices(), 6, renderer)
{
	SetPosition(position);
	SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));
	collider.width = width;
	collider.height = height;

	rendererInstance->SetData(trs, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

float* Rectangle::GetVertices(float width, float height)
{
	return new float[28]
		{
			width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				-width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
}

unsigned int* Rectangle::GetIndices()
{
	return new unsigned int[6]
		{
			0, 1, 3,
				1, 2, 3
		};
}
