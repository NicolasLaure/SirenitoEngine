#include "Lightning/SpotLight.h"

SpotLight::SpotLight()
{
	color = Color::white();
}

SpotLight::SpotLight(Color color, Vector3 position, Vector3 direction, float innerAngle, float maxAngle)
{
	this->color = color;
	this->innerAngle = innerAngle;
	outerAngle = maxAngle;
	this->direction = direction;
	transform.SetPosition(position);
}

Vector3 SpotLight::GetDirection()
{
	return direction;
}
