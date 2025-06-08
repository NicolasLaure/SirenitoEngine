#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/BaseLight.h"

SIRENITO_API class DirectionalLight : BaseLight
{
public:
	Color color;

	SIRENITO_API DirectionalLight();
	SIRENITO_API DirectionalLight(Color color, Vector3 eulers);
	SIRENITO_API Vector3 GetDirection();
};