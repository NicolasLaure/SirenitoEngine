#include "Lightning/DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	color = Color::white();
	transform.SetRotation(Quaternion::Euler(-90.0f, 0.0f, 0.0f));
}

DirectionalLight::DirectionalLight(Color color, Vector3 direction)
{
	this->color = color;
	this->direction = direction;
}
