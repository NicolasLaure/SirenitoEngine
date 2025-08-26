#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"
#include "math.h"
#include "MathConstants.h"
#include "Utilities/Vector2.h"
#include <string>

SIRENITO_API class Vector3
{
public:
#pragma region Variables

	float x;
	float y;
	float z;

	SIRENITO_API float sqrMagnitude()
	{
		return (x * x + y * y + z * z);
	}

	SIRENITO_API Vector3 normalized()
	{
		float mag = magnitude();
		return Vector3(x / mag, y / mag, z / mag);
	}


	SIRENITO_API float magnitude()
	{
		return sqrtf(sqrMagnitude());
	}

#pragma endregion

#pragma region Default Values

	SIRENITO_API static Vector3 Zero()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	SIRENITO_API static Vector3 One()
	{
		return Vector3(1.0f, 1.0f, 1.0f);
	}


	SIRENITO_API static Vector3 Forward()
	{
		return Vector3(0.0f, 0.0f, 1.0f);
	}


	SIRENITO_API static Vector3 Back()
	{
		return Vector3(0.0f, 0.0f, -1.0f);
	}


	SIRENITO_API static Vector3 Right()
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}


	SIRENITO_API static Vector3 Left()
	{
		return Vector3(-1.0f, 0.0f, 0.0f);
	}


	SIRENITO_API static Vector3 Up()
	{
		return Vector3(0.0f, 1.0f, 0.0f);
	}


	SIRENITO_API static Vector3 Down()
	{
		return Vector3(0.0f, -1.0f, 0.0f);
	}

#pragma endregion

#pragma region Constructors

	SIRENITO_API Vector3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}
	SIRENITO_API ~Vector3();
	SIRENITO_API Vector3(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0.0f;
	}

	SIRENITO_API Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	SIRENITO_API Vector3(Vector2 v2)
	{
		this->x = v2.x;
		this->y = v2.y;
		this->z = 0.0f;
	}

	SIRENITO_API Vector3(glm::vec3 v3)
	{
		x = v3.x;
		y = v3.y;
		z = v3.z;
	}
#pragma endregion

#pragma region Operators

	SIRENITO_API bool operator ==(Vector3 right)
	{
		float diff_x = this->x - right.x;
		float diff_y = this->y - right.y;
		float diff_z = this->z - right.z;
		float sqrmag = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;
		//Checks if the difference between both vectors is close to zero
		return sqrmag < KEpsilon* KEpsilon;
	}

	SIRENITO_API bool operator !=(Vector3 right)
	{
		return !(*this == right);
	}

	SIRENITO_API Vector3 operator +(Vector3 rightV3)
	{
		return Vector3(this->x + rightV3.x, this->y + rightV3.y, this->z + rightV3.z);
	}

	SIRENITO_API Vector3 operator -(Vector3 rightV3)
	{
		return Vector3(this->x - rightV3.x, this->y - rightV3.y, this->z - rightV3.z);
	}

	SIRENITO_API Vector3 operator *(float scalar)
	{
		return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
	}
	SIRENITO_API void operator *=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	SIRENITO_API Vector3 operator /(float scalar)
	{
		return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
	}
	SIRENITO_API void operator /=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
	}

#pragma endregion

#pragma region Functions

	SIRENITO_API glm::vec3 ToGlm();
	SIRENITO_API static Vector3 FromGlm(glm::vec3 glmVec3);

	SIRENITO_API static float Angle(Vector3 from, Vector3 to)
	{
		// by definition dot product a.b = |a||b| cos(O) disclaimer: O represents the symbol theta NOT A ZERO
		// divide each side by |a||b| and cos = dot / |a||b| 
		if (from.magnitude() == 0 || to.magnitude() == 0)
			return 0;

		return acosf(Vector3::Dot(from, to) / (from.magnitude() * to.magnitude())) * Rad2Deg;
	}

	SIRENITO_API static Vector3 ClampMagnitude(Vector3 vector, float maxLength)
	{
		if (vector.magnitude() > maxLength)
		{
			vector.Normalize();
			return vector * maxLength;
		}

		return vector;
	}

	SIRENITO_API static float Magnitude(Vector3 vector)
	{
		return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	SIRENITO_API static Vector3 Cross(Vector3 a, Vector3 b)
	{
		Vector3 normal = Vector3();

		normal.x = a.y * b.z - a.z * b.y;
		// for the "y" axis, we change the order of substraction to invert the value (since x and z remain positive while y is negative due to matrix sign) 
		normal.y = a.z * b.x - a.x * b.z;
		normal.z = a.x * b.y - a.y * b.x;

		return normal;
	}

	SIRENITO_API static float Distance(Vector3 a, Vector3 b)
	{
		return (a - b).magnitude();
	}

	SIRENITO_API static float Dot(Vector3 a, Vector3 b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	SIRENITO_API static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		t = glm::clamp(t, 0.0f, 1.0f);
		// the first vector plus the distance of itself to the second vector multiplied by t (0 returns a, 1 returns b)
		return a + (b - a) * t;
	}

	SIRENITO_API static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t)
	{
		return a + (b - a) * t;
	}

	SIRENITO_API static Vector3 Max(Vector3 a, Vector3 b)
	{
		Vector3 max;
		max.x = a.x > b.x ? a.x : b.x;
		max.y = a.y > b.y ? a.y : b.y;
		max.z = a.z > b.z ? a.z : b.z;

		return max;
	}

	SIRENITO_API static Vector3 Min(Vector3 a, Vector3 b)
	{
		Vector3 min;
		min.x = a.x < b.x ? a.x : b.x;
		min.y = a.y < b.y ? a.y : b.y;
		min.z = a.z < b.z ? a.z : b.z;

		return min;
	}

	SIRENITO_API static float SqrMagnitude(Vector3 vector)
	{
		return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	SIRENITO_API static Vector3 Project(Vector3 vector, Vector3 onNormal)
	{
		if (onNormal.magnitude() == 0)
			return Vector3::Zero();

		// https://www.geogebra.org/m/arPXpSet search why dotProduct(a,b) / b equals project
		onNormal.Normalize();
		onNormal *= (Dot(vector, onNormal) / sqrtf(powf(onNormal.x, 2) + powf(onNormal.y, 2) + powf(onNormal.z, 2)));
		return onNormal;
	}

	SIRENITO_API static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal)
	{
		return inDirection - (inNormal * 2) * Dot(inDirection, inNormal);
	}

	SIRENITO_API void Set(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	SIRENITO_API void Scale(Vector3 scale)
	{
		x *= scale.x;
		y *= scale.y;
		z *= scale.z;
	}

	SIRENITO_API void Normalize()
	{
		if (magnitude() == 0)
			return;

		float newX = x / magnitude();
		float newY = y / magnitude();
		float newZ = z / magnitude();
		x = newX;
		y = newY;
		z = newZ;
	}

	SIRENITO_API static Vector3 Normalize(Vector3 value)
	{
		float magnitude = value.magnitude();
		if (magnitude == 0)
			return Vector3(0, 0, 0);

		float newX = value.x / magnitude;
		float newY = value.y / magnitude;
		float newZ = value.z / magnitude;
		return Vector3(newX, newY, newZ);
	}

	SIRENITO_API std::string ToString()
	{
		std::string str = std::string("x: ");
		str.append(std::to_string(x));
		str.append(", y: ");
		str.append(std::to_string(y));
		str.append(", z: ");
		str.append(std::to_string(z));
		return str;
	}

#pragma endregion
};
