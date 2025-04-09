#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"
#include "Utilities/MathConstants.h"
#include "Utilities/Vector3.h"
#include "Utilities/Vector4.h"
#include "Utilities/Quaternion.h"
#include "Utilities/MY4X4.h"
#include <math.h>

SIRENITO_API class TRS
{
public:
	MY4X4 trsMatrix;

	SIRENITO_API TRS(Vector3 pos, Quaternion q, Vector3 s)
	{
		trsMatrix = MY4X4::Translate(pos) * Rotate(q) * MY4X4::Scale(s);
	}

	SIRENITO_API Quaternion rotation()
	{
		Quaternion q = Quaternion::identity();
		MY4X4 m = MY4X4(trsMatrix.GetColumn(0), trsMatrix.GetColumn(1), trsMatrix.GetColumn(2), trsMatrix.GetColumn(3));
		Vector3 scale = trsMatrix.GetlossyScale();

		float m00 = *trsMatrix.GetPointerAt(0, 0) /= scale.x;
		float m01 = *trsMatrix.GetPointerAt(0, 1) /= scale.y;
		float m02 = *trsMatrix.GetPointerAt(0, 2) /= scale.z;
		float m10 = *trsMatrix.GetPointerAt(1, 0) /= scale.x;
		float m11 = *trsMatrix.GetPointerAt(1, 1) /= scale.y;
		float m12 = *trsMatrix.GetPointerAt(1, 2) /= scale.z;
		float m20 = *trsMatrix.GetPointerAt(2, 0) /= scale.x;
		float m21 = *trsMatrix.GetPointerAt(2, 1) /= scale.y;
		float m22 = *trsMatrix.GetPointerAt(2, 2) /= scale.z;

		q.w = glm::sqrt(glm::max(0.0f, 1 + m00 + m11 + m22)) / 2;
		q.x = glm::sqrt(glm::max(0.0f, 1 + m00 - m11 - m22)) / 2;
		q.y = glm::sqrt(glm::max(0.0f, 1 - m00 + m11 - m22)) / 2;
		q.z = glm::sqrt(glm::max(0.0f, 1 - m00 - m11 + m22)) / 2;

		q.x *= glm::sign(q.x * m21 - m12);
		q.y *= glm::sign(q.y * m02 - m20);
		q.z *= glm::sign(q.z * m10 - m01);

		return q.normalized();
	}

	//
	// Summary:
	//     Create a "look at" matrix.
	//
	// Parameters:
	//   from:
	//     The source point.
	//
	//   to:
	//     The target point.
	//
	//   up:
	//     The vector describing the up direction (typically Vector3.up).
	//
	// Returns:
	//     The resulting transformation matrix.
	SIRENITO_API static MY4X4 LookAt(Vector3 from, Vector3 to, Vector3 up)
	{
		return TRS(from, Quaternion::LookRotation(to - from, up), Vector3::One()).trsMatrix;
	}

	//
	// Summary:
	//     Creates a rotation matrix.
	//
	// Parameters:
	//   q:
	SIRENITO_API static MY4X4 Rotate(Quaternion q)
	{
		Quaternion rotation = q;
		rotation.Normalize();

		Vector4 firstColumn = Vector4(2.0f * (rotation.w * rotation.w + rotation.x * rotation.x) - 1,
			2.0f * (rotation.x * rotation.y + rotation.w * rotation.z),
			2.0f * (rotation.x * rotation.z - rotation.w * rotation.y),
			0.0f);

		Vector4 secondColumn = Vector4(2.0f * (rotation.x * rotation.y - rotation.w * rotation.z),
			2.0f * (rotation.w * rotation.w + rotation.y * rotation.y) - 1,
			2.0f * (rotation.y * rotation.z + rotation.w * rotation.x),
			0.0f);

		Vector4 thirdColumn = Vector4(2.0f * (rotation.x * rotation.z + rotation.w * rotation.y),
			2.0f * (rotation.y * rotation.z - rotation.w * rotation.x),
			2.0f * (rotation.w * rotation.w + rotation.z * rotation.z) - 1,
			0.0f);

		Vector4 fourthColumn = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		return MY4X4(firstColumn, secondColumn, thirdColumn, fourthColumn);
	}

	//
	// Summary:
	//     Sets this matrix to a translation, rotation and scaling matrix.
	//
	// Parameters:
	//   pos:
	//
	//   q:
	//
	//   s:
	SIRENITO_API void SetTRS(Vector3 pos, Quaternion q, Vector3 s)
	{
		MY4X4 trs = TRS(pos, q, s).trsMatrix;

		for (int i = 0; i < 4; i++)
		{
			trsMatrix.SetColumn(i, trs.GetColumn(i));
		}
	}
};