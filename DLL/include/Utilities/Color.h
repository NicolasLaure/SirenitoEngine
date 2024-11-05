#pragma once
#include "Utilities/Exporter.h"

SIRENITO_API class Color
{
public:
	float r;
	float g;
	float b;
	float a;

	SIRENITO_API Color();
	SIRENITO_API Color(float r, float g, float b, float a);

	SIRENITO_API static Color white();
	SIRENITO_API static Color black();
	SIRENITO_API static Color red();
	SIRENITO_API static Color green();
	SIRENITO_API static Color blue();
};
