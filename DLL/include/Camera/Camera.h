#pragma once
#include "glm.hpp"

class Camera
{
private:
	glm::mat4 view;

public:
	Camera();

	glm::mat4 GetViewMatrix();
	void SetViewMatrix(glm::mat4 newView);
	void Translate(glm::vec3 translation);
};