#include "Utilities/Vector2.h"

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
}

glm::vec2 Vector2::ToGlm()
{
	return glm::vec2(x, y);
}

Vector2 Vector2::FromGlm(glm::vec2 vec2)
{
	return Vector2(vec2.x, vec2.y);
}

void Vector2::operator=(Vector2 right)
{
	x = right.x;
	y = right.y;
}

Vector2 Vector2::operator+(Vector2 right)
{
	return Vector2(this->x + right.x, this->y + right.y);
}

Vector2 Vector2::operator-(Vector2 right)
{
	return Vector2(this->x - right.x, this->y - right.y);
}

Vector2 Vector2::operator*(float scale)
{
	return Vector2(x * scale, y * scale);
}

bool Vector2::operator == (Vector2 right)
{
	float diff_x = this->x - right.x;
	float diff_y = this->y - right.y;

	float sqrmag = diff_x * diff_x + diff_y * diff_y;
	return sqrmag < epsilon * epsilon;
}

bool Vector2::operator != (Vector2 right)
{
	return !(*this == right);
}
