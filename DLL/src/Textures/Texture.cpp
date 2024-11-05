#include "Textures/Texture.h"

Texture::Texture()
{
	ID = 0;
	width = 0;
	height = 0;
}
Texture::Texture(unsigned int ID, int width, int height)
{
	this->ID = ID;
	this->width = width;
	this->height = height;
}
Texture::~Texture()
{
}

unsigned int Texture::GetId()
{
	return ID;
}
int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}