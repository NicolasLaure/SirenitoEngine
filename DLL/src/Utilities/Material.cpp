#include "Utilities/Material.h"

Material::Material()
{
	tint = Color::white();
}

Material::Material(Color tint)
{
	this->tint = tint;
}

Material::Material(Color tint, float glossiness)
{
	this->tint = tint;
	this->glossiness = glossiness;
}
