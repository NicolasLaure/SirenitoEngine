#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/Color.h"

SIRENITO_API class Material
{
public:
	Color tint;
	float glossiness = 0.5f;

	SIRENITO_API Material();
	SIRENITO_API Material(Color tint);
	SIRENITO_API Material(Color tint, float glossiness);
};
