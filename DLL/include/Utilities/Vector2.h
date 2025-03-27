#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"

SIRENITO_API class Vector2
{
private:
	const float epsilon = 1e-05f;

public:
	float x;
	float y;

	SIRENITO_API Vector2();
	SIRENITO_API Vector2(float x, float y);
	SIRENITO_API ~Vector2();

	SIRENITO_API glm::vec2 ToGlm();
	SIRENITO_API static Vector2 FromGlm(glm::vec2 vec2);

	SIRENITO_API void operator = (Vector2 right);
	SIRENITO_API Vector2 operator + (Vector2 right);
	SIRENITO_API Vector2 operator - (Vector2 right);
	SIRENITO_API Vector2 operator * (float scale);
	SIRENITO_API bool operator == (Vector2 right);
	SIRENITO_API bool operator != (Vector2 right);
};