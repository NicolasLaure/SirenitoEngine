#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"
#include "Utilities/Transform.h"

SIRENITO_API class Camera
{
public:
	Transform* view;

	SIRENITO_API Camera();
	SIRENITO_API ~Camera();

	SIRENITO_API glm::mat4 GetViewMatrix();
	SIRENITO_API void Translate(Vector3 translation);
	SIRENITO_API void Rotate(Vector3 eulers);
	SIRENITO_API void Rotate(Vector3 axis, float angle);
};