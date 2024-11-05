#include "Camera/Camera.h"

#include "gtc/matrix_transform.hpp"

Camera::Camera()
{
	view = glm::identity<glm::mat4>();
}

glm::mat4 Camera::GetViewMatrix()
{
	return view;
}

void Camera::SetViewMatrix(glm::mat4 newView)
{
	view = newView;
}

void Camera::Translate(glm::vec3 translation)
{
	view = glm::translate(view, -translation);
}
