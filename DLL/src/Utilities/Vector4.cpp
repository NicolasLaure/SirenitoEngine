#include "Utilities/Vector4.h"

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0.0f;
}

float Vector4::sqrMagnitude()
{
	return (x * x + y * y + z * z + w * w);
}

float Vector4::magnitude()
{
	return sqrtf(sqrMagnitude());
}

Vector4 Vector4::zero()
{
	return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::one()
{
	return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector4 Vector4::operator *(float scalar)
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

void Vector4::operator *=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
}

Vector4 Vector4::operator/(float scalar)
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

void Vector4::operator /=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
}
