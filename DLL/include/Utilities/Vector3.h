#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"

SIRENITO_API class Vector3
{
public:
	float x;
	float y;
	float z;

	SIRENITO_API Vector3();
	SIRENITO_API Vector3(float x, float y, float z);
	SIRENITO_API ~Vector3();

	SIRENITO_API glm::vec3 ToGlm();
	SIRENITO_API static Vector3 FromGlm(glm::vec3 vec3);

	SIRENITO_API Vector3 operator + (Vector3 right);
	SIRENITO_API Vector3 operator - (Vector3 right);
	SIRENITO_API Vector3 operator * (float scale);
};
