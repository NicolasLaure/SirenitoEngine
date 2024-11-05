#pragma once
#include "Utilities/Exporter.h"

SIRENITO_API class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	SIRENITO_API Quaternion();
	SIRENITO_API Quaternion(float x, float y, float z, float w);
	SIRENITO_API ~Quaternion();
};