#pragma once
#include "Utilities/Exporter.h"
#include "stb_image.h"
#include "Textures/Texture.h"

SIRENITO_API class TextureImporter
{
public:
	SIRENITO_API TextureImporter();
	SIRENITO_API static Texture ImportTexture(const char* path);
};