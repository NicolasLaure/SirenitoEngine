#include "Camera/Camera.h"

Camera::Camera()
{
	view = new Transform("Camera");
}

Camera::~Camera()
{
	delete view;
}

glm::mat4 Camera::GetViewMatrix()
{
	return view->LocalToWorldMatrix().ToGlm();
}

void Camera::Translate(Vector3 translation)
{
	view->Translate(translation * -1);
}

void Camera::Rotate(Vector3 eulers)
{
	view->Rotate(eulers);
}

void Camera::Rotate(Vector3 axis, float angle)
{
	view->Rotate(axis, angle);
}
