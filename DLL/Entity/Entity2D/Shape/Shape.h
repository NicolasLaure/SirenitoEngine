#pragma once

#include "Entity/Entity2D/Entity2D.h"
#include "Utilities/Vector2.h"
#include "Utilities/Exporter.h"

SIRENITO_API class Shape : public Entity2D
{
private:
	int vertexQty;

public:
	Vector2f* vertices;

	SIRENITO_API Shape(Vector2f vertices[], int vertexQty);
	SIRENITO_API ~Shape();

	SIRENITO_API void Draw(Renderer rendererInstance) override;
};
