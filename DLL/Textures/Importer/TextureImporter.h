#pragma once
#include "Utilities/Exporter.h"
#include "stb_image.h"

SIRENITO_API class TextureImporter
{
public:
	SIRENITO_API TextureImporter();
	SIRENITO_API static unsigned int ImportTexture(const char* path);
};