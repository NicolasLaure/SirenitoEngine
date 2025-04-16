#pragma once
#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Vector4.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/quaternion.hpp"
#include <math.h>
#include "Utilities/MathConstants.h"


SIRENITO_API class Quaternion
{
public:
#pragma region Variables

	float x;
	float y;
	float z;
	float w;

	SIRENITO_API Vector3 eulerAngles()
	{
		float xValue = x * w - y * z;
		Vector3 result = Vector3::Zero();

		if (xValue > 0.4999f * sqrMagnitude())
		{
			result.y = 2.0f * atan2f(y, x);
			result.x = PI / 2;
			result.z = 0;

			return result * Rad2Deg;
		}

		if (xValue < -0.4999f * sqrMagnitude())
		{
			result.y = -2.0f * atan2f(y, x);
			result.x = -PI / 2;
			result.z = 0;
			return result * Rad2Deg;
		}

		Quaternion quaternion = Quaternion(w, z, x, y);
		result.y = atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
		result.x = asinf(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
		result.z = atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
		return result * Rad2Deg;
	}
	SIRENITO_API void SetEulerAngles(Vector3 value)
	{
		Quaternion q = Euler(value);
		Set(q.x, q.y, q.z, q.w);
	}

	SIRENITO_API float sqrMagnitude()
	{
		return w * w + x * x + y * y + z * z;
	}


	SIRENITO_API float magnitude()
	{
		return sqrtf(sqrMagnitude());
	}

	SIRENITO_API Quaternion normalized()
	{
		return Quaternion(x / magnitude(), y / magnitude(), z / magnitude(), w / magnitude());
	}


#pragma endregion

#pragma region DefaultValues

	SIRENITO_API static Quaternion identity()
	{
		return Quaternion(0, 0, 0, 1);
	}

#pragma endregion

#pragma region Constructors

	SIRENITO_API Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

#pragma endregion

#pragma region Operators

	SIRENITO_API Vector3 operator *(Vector3 point)
	{
		Quaternion pureVectorQuaternion = Quaternion(point.x, point.y, point.z, 0);
		Quaternion appliedPureQuaternion = *this * pureVectorQuaternion * Quaternion::Conjugated(*this);

		return Vector3(appliedPureQuaternion.x, appliedPureQuaternion.y, appliedPureQuaternion.z);
	}

	SIRENITO_API Quaternion operator *(Quaternion rhs)
	{
		return Quaternion(
			this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
			this->w * rhs.y - this->x * rhs.z + this->y * rhs.w + this->z * rhs.x,
			this->w * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.w,
			this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z);
	}

	SIRENITO_API bool operator ==(Quaternion rhs)
	{
		float diff_x = this->x - rhs.x;
		float diff_y = this->y - rhs.y;
		float diff_z = this->z - rhs.z;
		float diff_w = this->w - rhs.w;
		float sqrmag = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z + diff_w * diff_w;
		return sqrmag < KEpsilon * KEpsilon;
	}

	SIRENITO_API bool operator !=(Quaternion rhs)
	{
		return !(*this == rhs);
	}

#pragma endregion

#pragma region Functions

	SIRENITO_API static float Angle(Quaternion a, Quaternion b)
	{
		float dotAbs = glm::abs(Dot(a, b));
		return a == b ? 0.0f : acosf(glm::min(dotAbs, 1.0f)) * 2 * Rad2Deg;
	}

	SIRENITO_API static Quaternion AngleAxis(float angle, Vector3 axis)
	{
		axis.Normalize();
		axis *= sinf(angle * Deg2Rad * 0.5f);
		return Quaternion(axis.x, axis.y, axis.z, cosf(angle * Deg2Rad * 0.5f));
	}

	SIRENITO_API static float Dot(Quaternion a, Quaternion b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	SIRENITO_API static Quaternion Euler(Vector3 euler)
	{
		Quaternion qx = identity();
		Quaternion qy = identity();
		Quaternion qz = identity();

		float halfAngleToRadians = Deg2Rad * 0.5f;
		qz.Set(0, 0, sinf(euler.z * halfAngleToRadians), cosf(euler.z * halfAngleToRadians));
		qx.Set(sinf(euler.x * halfAngleToRadians), 0, 0, cosf(euler.x * halfAngleToRadians));
		qy.Set(0, sinf(euler.y * halfAngleToRadians), 0, cosf(euler.y * halfAngleToRadians));

		return qy * qx * qz;
	}

	SIRENITO_API static Quaternion Euler(float x, float y, float z)
	{
		Quaternion qx = identity();
		Quaternion qy = identity();
		Quaternion qz = identity();

		float halfAngleToRadians = Deg2Rad * 0.5f;
		qz.Set(0, 0, sinf(z * halfAngleToRadians), cosf(z * halfAngleToRadians));
		qx.Set(sinf(x * halfAngleToRadians), 0, 0, cosf(x * halfAngleToRadians));
		qy.Set(0, sinf(y * halfAngleToRadians), 0, cosf(y * halfAngleToRadians));

		return qy * qx * qz;
	}

	SIRENITO_API static Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection)
	{
		Vector3 axis = Vector3::Cross(fromDirection, toDirection);
		float angle = Vector3::Angle(fromDirection, toDirection);
		return AngleAxis(angle, axis.normalized());
	}

	SIRENITO_API static Quaternion Inverse(Quaternion rotation)
	{
		return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
	}

	SIRENITO_API static Quaternion Lerp(Quaternion a, Quaternion b, float t)
	{
		Quaternion result = identity();

		t = glm::clamp(t, 0.0f, 1.0f);
		float timeLeft = 1 - t;
		if (Dot(a, b) >= 0)
		{
			result.x = (timeLeft * a.x) + (t * b.x);
			result.y = (timeLeft * a.y) + (t * b.y);
			result.z = (timeLeft * a.z) + (t * b.z);
			result.w = (timeLeft * a.w) + (t * b.w);
		}
		else
		{
			result.x = (timeLeft * a.x) - (t * b.x);
			result.y = (timeLeft * a.y) - (t * b.y);
			result.z = (timeLeft * a.z) - (t * b.z);
			result.w = (timeLeft * a.w) - (t * b.w);
		}

		result.Normalize();
		return result;
	}

	SIRENITO_API static Quaternion LerpUnclamped(Quaternion a, Quaternion b, float t)
	{
		Quaternion result = identity();

		float timeLeft = 1 - t;
		if (Dot(a, b) >= 0)
		{
			result.x = (timeLeft * a.x) + (t * b.x);
			result.y = (timeLeft * a.y) + (t * b.y);
			result.z = (timeLeft * a.z) + (t * b.z);
			result.w = (timeLeft * a.w) + (t * b.w);
		}
		else
		{
			result.x = (timeLeft * a.x) - (t * b.x);
			result.y = (timeLeft * a.y) - (t * b.y);
			result.z = (timeLeft * a.z) - (t * b.z);
			result.w = (timeLeft * a.w) - (t * b.w);
		}

		result.Normalize();
		return result;
	}

	SIRENITO_API static Quaternion LookRotation(Vector3 forward)
	{
		forward.Normalize();
		Vector3 right = Vector3::Normalize(Vector3::Cross(Vector3::Up(), forward));
		Vector3 up = Vector3::Normalize(Vector3::Cross(forward, right));

		float m00 = right.x;
		float m01 = right.y;
		float m02 = right.z;
		float m10 = up.x;
		float m11 = up.y;
		float m12 = up.z;
		float m20 = forward.x;
		float m21 = forward.y;
		float m22 = forward.z;

		float diagonals = m00 + m11 + m22;

		Quaternion q = Quaternion::identity();

		if (diagonals > 0.0f)
		{
			float num = sqrtf(diagonals + 1);
			q.w = num * 0.5f;
			num = 0.5f / num;
			q.x = (m12 - m21) * num;
			q.y = (m20 - m02) * num;
			q.z = (m01 - m10) * num;
			return q;
		}

		if (m00 >= m11 && m00 >= m22)
		{
			float num = sqrtf(1 + m00 - m11 - m22);
			q.x = num * 0.5f;
			num = 0.5f / num;
			q.y = (m01 + m10) * num;
			q.z = (m20 + m02) * num;
			q.w = (m12 - m21) * num;
			return q;
		}

		if (m11 > m22)
		{
			float num = sqrtf(1 + m11 - m00 - m22);
			q.y = num * 0.5f;
			num = 0.5f / num;
			q.x = (m01 + m10) * num;
			q.z = (m12 + m21) * num;
			q.w = (m20 - m02) * num;
			return q;
		}

		float num1 = sqrtf(1 + m22 - m00 - m11);
		q.z = num1 * 0.5f;
		num1 = 0.5f / num1;
		q.x = (m20 + m02) * num1;
		q.y = (m21 + m12) * num1;
		q.w = (m01 - m10) * num1;
		return q;
	}

	SIRENITO_API static Quaternion LookRotation(Vector3 forward, Vector3 upwards)
	{
		forward.Normalize();
		Vector3 right = Vector3::Normalize(Vector3::Cross(upwards, forward));
		upwards = Vector3::Normalize(Vector3::Cross(forward, right));
		float m00 = right.x;
		float m01 = right.y;
		float m02 = right.z;
		float m10 = upwards.x;
		float m11 = upwards.y;
		float m12 = upwards.z;
		float m20 = forward.x;
		float m21 = forward.y;
		float m22 = forward.z;

		float diagonals = m00 + m11 + m22;

		Quaternion q = Quaternion::identity();

		if (diagonals > 0.0f)
		{
			float num = sqrtf(diagonals + 1);
			q.w = num * 0.5f;
			num = 0.5f / num;
			q.x = (m12 - m21) * num;
			q.y = (m20 - m02) * num;
			q.z = (m01 - m10) * num;
			return q;
		}

		if (m00 >= m11 && m00 >= m22)
		{
			float num = sqrtf(1 + m00 - m11 - m22);
			q.x = num * 0.5f;
			num = 0.5f / num;
			q.y = (m01 + m10) * num;
			q.z = (m20 + m02) * num;
			q.w = (m12 - m21) * num;
			return q;
		}

		if (m11 > m22)
		{
			float num = sqrtf(1 + m11 - m00 - m22);
			q.y = num * 0.5f;
			num = 0.5f / num;
			q.x = (m01 + m10) * num;
			q.z = (m12 + m21) * num;
			q.w = (m20 - m02) * num;
			return q;
		}

		float num1 = sqrtf(1 + m22 - m00 - m11);
		q.z = num1 * 0.5f;
		num1 = 0.5f / num1;
		q.x = (m20 + m02) * num1;
		q.y = (m21 + m12) * num1;
		q.w = (m01 - m10) * num1;
		return q;
	}

	SIRENITO_API static Quaternion Normalize(Quaternion q)
	{
		return Quaternion(q.x / q.magnitude(), q.y / q.magnitude(), q.z / q.magnitude(), q.w / q.magnitude());
	}

	SIRENITO_API static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta)
	{
		if (Dot(from.normalized(), to.normalized()) >= 1 - KEpsilon || Dot(from.normalized(), to.normalized()) <= -1 + KEpsilon)
		{
			return to;
		}

		float angle = Angle(from, to);
		return LerpUnclamped(from, to, maxDegreesDelta / angle);
	}

	SIRENITO_API static Quaternion Slerp(Quaternion a, Quaternion b, float t)
	{
		t = glm::clamp(t, 0.0f, 1.0f);
		return SlerpUnclamped(a, b, t);
	}

	SIRENITO_API static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t)
	{
		float cosAngle = Dot(a, b);

		float angle = acosf(glm::abs(cosAngle));
		float sinAngle = sinf(angle);
		float quatAWeight = sinf(angle * (1.0f - t)) / sinAngle;
		float quatBWeight = sinf(angle * t) / sinAngle;

		if (cosAngle < 0)
			quatAWeight = -quatAWeight;

		Quaternion res = identity();

		res.x = quatAWeight * a.x + quatBWeight * b.x;
		res.y = quatAWeight * a.y + quatBWeight * b.y;
		res.z = quatAWeight * a.z + quatBWeight * b.z;
		res.w = quatAWeight * a.w + quatBWeight * b.w;

		return res;
	}

	SIRENITO_API void Normalize()
	{
		float originalMagnitude = magnitude();

		x /= originalMagnitude;
		y /= originalMagnitude;
		z /= originalMagnitude;
		w /= originalMagnitude;
	}

	SIRENITO_API void Set(float newX, float newY, float newZ, float newW)
	{
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}

	SIRENITO_API void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection)
	{
		Vector3 axis = Vector3::Cross(fromDirection, toDirection);
		float angle = Vector3::Angle(fromDirection, toDirection);
		Quaternion result = AngleAxis(angle, axis.normalized());
		x = result.x;
		y = result.y;
		z = result.z;
		w = result.w;
	}

	SIRENITO_API void SetLookRotation(Vector3 view)
	{
		Quaternion q = LookRotation(view);

		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
		this->w = q.w;
	}

	SIRENITO_API void SetLookRotation(Vector3 view, Vector3 up)
	{
		Quaternion q = LookRotation(view, up);

		this->x = q.x;
		this->y = q.y;
		this->z = q.z;
		this->w = q.w;
	}

	SIRENITO_API void ToAngleAxis(float* angle, Vector3* axis)
	{
		Normalize();
		*angle = 2.0f * acosf(w) * Rad2Deg;
		float mag = sqrtf(1.0f - w * w);
		if (mag > 0.0001f)
		{
			*axis = Vector3(x, y, z) / mag;
		}
		else
		{
			*axis = Vector3(1, 0, 0);
		}
	}

	SIRENITO_API static Quaternion Conjugated(Quaternion q)
	{
		return Quaternion(-q.x, -q.y, -q.z, q.w);
	}

	SIRENITO_API glm::quat ToGlm()
	{
		return glm::quat(w, x, y, z);
	}
#pragma endregion

};
