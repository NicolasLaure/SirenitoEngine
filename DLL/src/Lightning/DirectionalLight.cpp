#include "Lightning/DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	color = Color::white();
	transform.SetRotation(Quaternion::Euler(-90.0f, 0.0f, 0.0f));
}

DirectionalLight::DirectionalLight(Color color, Vector3 eulers)
{
	this->color = color;
	transform.SetRotation(Quaternion::Euler(eulers));
}

Vector3 DirectionalLight::GetDirection()
{
	return transform.GetRotation() * Vector3::One();
}
