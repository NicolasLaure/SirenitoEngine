#include "Utilities/Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

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

Vector3 Vector3::operator+(Vector3 right)
{
	return Vector3(this->x + right.x, this->y + right.y, this->z + right.z);
}

Vector3 Vector3::operator-(Vector3 right)
{
	return Vector3(this->x - right.x, this->y - right.y, this->z - right.z);
}

Vector3 Vector3::operator*(float scale)
{
	return Vector3(x * scale, y * scale, z * scale);
}
