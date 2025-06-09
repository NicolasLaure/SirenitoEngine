#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/BaseLight.h"

SIRENITO_API class DirectionalLight : public BaseLight
{
public:
	Vector3 direction;

	SIRENITO_API DirectionalLight();
	SIRENITO_API DirectionalLight(Color material, Vector3 eulers);
};