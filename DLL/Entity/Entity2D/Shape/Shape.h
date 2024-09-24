#pragma once

#include "Entity/Entity2D/Entity2D.h"
#include "glm.hpp"
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"
#include "Utilities/Color.h"

SIRENITO_API class Shape : public Entity2D
{
protected:
	int vertexQty;
	int indexQty;
	float* vertices;
	unsigned int* indices;
	Color color;
public:

	SIRENITO_API Shape(glm::vec3 position, glm::vec3 eulers, Color color, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance);
	SIRENITO_API Shape(Color color, float* vertices, int vertexQty, unsigned int* indices, int indexQty, Renderer* rendererInstance);
	SIRENITO_API ~Shape();

	SIRENITO_API void Draw() override;
};
