#pragma once
#include <vector>
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Entity2D.h"

SIRENITO_API class CollisionManager
{
public:
	SIRENITO_API static bool CheckCollision(Entity2D entity, Entity2D other);
};
