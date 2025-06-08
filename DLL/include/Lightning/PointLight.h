#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/BaseLight.h"

SIRENITO_API class PointLight : public BaseLight
{
public:
	SIRENITO_API PointLight(Color color);
	SIRENITO_API PointLight(Color color, Vector3 position);

	SIRENITO_API Vector3 GetPosition();
};