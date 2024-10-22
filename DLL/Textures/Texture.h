#pragma once
#include "Utilities/Exporter.h"

SIRENITO_API class Texture
{
private:
	unsigned int ID;
	int width;
	int height;

public:
	Texture();
	Texture(unsigned int ID, int width, int height);
	~Texture();

	unsigned int GetId();
	int GetWidth();
	int GetHeight();
};