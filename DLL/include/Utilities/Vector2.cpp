#include "Vector2.h"

bool Vector2f::operator==(Vector2f other)
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2f::operator!=(Vector2f other)
{
	return !(*this == other);
}
