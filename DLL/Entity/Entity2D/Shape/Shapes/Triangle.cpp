#include "Triangle.h"

Triangle::Triangle(Vector3 position, float width, float height, Color color, Renderer* renderer) : Shape(color, GetVertices(width, height), 21, GetIndices(), 3, renderer)
{
	SetPosition(position);
	SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

float* Triangle::GetVertices(float width, float height)
{
	return new float[21]
		{
			//Positions								//Colors
			-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				0.0f, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};;
}

unsigned int* Triangle::GetIndices()
{
	return new unsigned int[3]
		{
			0, 1, 2,
		};
}