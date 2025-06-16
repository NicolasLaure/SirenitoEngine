#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"

SIRENITO_API struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Tint;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};