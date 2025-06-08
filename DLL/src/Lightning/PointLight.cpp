#include "Lightning/PointLight.h"

PointLight::PointLight(Color color)
{
	this->color = color;
}

PointLight::PointLight(Color color, Vector3 position)
{
	this->color = color;
	transform.Translate(position);
}

Vector3 PointLight::GetPosition()
{
	return transform.GetPosition();
}