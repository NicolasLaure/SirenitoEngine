#include "Utilities/Vector3.h"

Vector3::~Vector3()
{
}

glm::vec3 Vector3::ToGlm()
{
	return glm::vec3(x, y, z);
}

Vector3 Vector3::FromGlm(glm::vec3 vec3)
{
	return Vector3(vec3.x, vec3.y, vec3.z);
}