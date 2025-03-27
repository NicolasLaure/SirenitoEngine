#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"

SIRENITO_API class Camera
{
private:
	glm::mat4 view;

public:
	SIRENITO_API Camera();

	SIRENITO_API glm::mat4 GetViewMatrix();
	SIRENITO_API void SetViewMatrix(glm::mat4 newView);
	SIRENITO_API void Translate(glm::vec3 translation);
};