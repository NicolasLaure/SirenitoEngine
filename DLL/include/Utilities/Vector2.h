#pragma once

struct Vector2f
{
	float x;
	float y;

	bool operator == (Vector2f other);
	bool operator != (Vector2f other);
};