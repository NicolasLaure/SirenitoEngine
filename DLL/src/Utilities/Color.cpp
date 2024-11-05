#include "Utilities/Color.h"

Color::Color()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::white()
{
	return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::black()
{
	return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::red()
{
	return Color(1.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::green()
{
	return Color(0.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::blue()
{
	return Color(0.0f, 0.0f, 1.0f, 1.0f);
}