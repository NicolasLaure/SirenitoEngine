#include "Animation/Frame.h"

Frame::Frame()
{
	minCoords = Vector2(0.0f, 0.0f);
	maxCoords = Vector2(1.0f, 1.0f);
}

Frame::Frame(Vector2 minCoords, Vector2 maxCoords)
{
	this->minCoords = minCoords;
	this->maxCoords = maxCoords;
}

Vector2 Frame::GetMin()
{
	return minCoords;
}

Vector2 Frame::GetMax()
{
	return maxCoords;
}

bool Frame::operator==(Frame other)
{
	return this->minCoords == other.minCoords && this->maxCoords == other.maxCoords;
}

bool Frame::operator!=(Frame other)
{
	return !(*this == other);
}
