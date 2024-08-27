#pragma once

#include "Entity/Entity2D/Entity2D.h"
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"

SIRENITO_API class Shape : public Entity2D
{
private:
	int vertexQty;

public:
	float* vertices;

	SIRENITO_API Shape(float vertices[], int vertexQty, Renderer rendererInstance);
	SIRENITO_API ~Shape();

	SIRENITO_API void Draw(Renderer rendererInstance) override;
};
