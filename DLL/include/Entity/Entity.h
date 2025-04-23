#pragma once

#include "Utilities/Exporter.h"
#include "glm.hpp"

#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"

#include "Utilities/Transform.h"

SIRENITO_API class Entity
{
public:
	Transform transform;

	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();
};