#include "Animation/Frame.h"

Frame::Frame()
{
	minCoords = { 0.0f,0.0f };
	maxCoords = { 1.0f,1.0f };
}

Frame::Frame(Vector2f minCoords, Vector2f maxCoords)
{
	this->minCoords = minCoords;
	this->maxCoords = maxCoords;
}

Vector2f Frame::GetMin()
{
	return minCoords;
}

Vector2f Frame::GetMax()
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
