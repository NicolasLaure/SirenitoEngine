#pragma once
#include "Utilities/Exporter.h"
#include <math.h>

SIRENITO_API class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	SIRENITO_API Vector4();
	SIRENITO_API Vector4(float x, float y, float z, float w);
	SIRENITO_API Vector4(float x, float y);
	SIRENITO_API Vector4(float x, float y, float z);

	SIRENITO_API float sqrMagnitude();
	SIRENITO_API float magnitude();

	SIRENITO_API static Vector4 zero();
	SIRENITO_API static Vector4 one();

	SIRENITO_API Vector4 operator *(float scalar);
	SIRENITO_API void operator *=(float scalar);
	SIRENITO_API Vector4 operator /(float scalar);
	SIRENITO_API void operator /=(float scalar);

};