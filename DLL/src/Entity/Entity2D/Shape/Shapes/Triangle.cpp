#include "Entity/Entity2D/Shape/Shapes/Triangle.h"

Triangle::Triangle(Vector3 position, float width, float height, Color color, Renderer* renderer) : Shape(color, GetTransformedVertices(width, height), 21, GetIndices(), 3, renderer)
{
	transform = new Transform();
	transform->SetPosition(position);
	rendererInstance->SetData(transform, color, false, vertices, vertexQty, indices, indexQty, VAO, VBO, EBO);
}

Triangle::~Triangle()
{
	delete transform;
}

float* Triangle::GetTransformedVertices(float width, float height)
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