#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(unsigned int ID, float width, float height)
{
	this->ID = ID;
	this->width = width;
	this->height = height;
}

unsigned int Texture::GetId()
{
	return ID;
}
