#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/BaseLight.h"

SIRENITO_API class SpotLight : public BaseLight
{
public:
	Vector3 direction;
	float outerAngle = 10.0f;
	float innerAngle = 7.5f;

	SIRENITO_API SpotLight();
	SIRENITO_API SpotLight(Color color, Vector3 position, Vector3 direction, float innerAngle, float maxAngle);

	Vector3 GetDirection();
};
