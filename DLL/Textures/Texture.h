#pragma once
#include "Utilities/Exporter.h"

SIRENITO_API class Texture
{
private:
	unsigned int ID;
	float width;
	float height;

public:
	SIRENITO_API Texture();
	SIRENITO_API Texture(unsigned int ID, float width, float height);

	SIRENITO_API unsigned int GetId();
};