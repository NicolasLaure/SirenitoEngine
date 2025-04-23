#pragma once
#include "Utilities/Exporter.h"
#include "glm.hpp"
#include "Utilities/MathConstants.h"
#include "Utilities/Vector3.h"
#include "Utilities/Vector4.h"
#include "Utilities/Quaternion.h"
#include <math.h>

SIRENITO_API class MY4X4
{
public:
#pragma region  Variables

	float m00;
	float m33;
	float m23;
	float m13;
	float m03;
	float m32;
	float m22;
	float m02;
	float m12;
	float m21;
	float m11;
	float m01;
	float m30;
	float m20;
	float m10;
	float m31;


	//
	// Summary:
	//     Attempts to get a scale value from the matrix. (Read Only)
	SIRENITO_API Vector3 GetlossyScale()
	{
		return Vector3(GetColumn(0).magnitude(), GetColumn(1).magnitude(), GetColumn(2).magnitude());
	}

	//
	// Summary:
	//     Checks whether this is an identity matrix. (Read Only)
	SIRENITO_API bool isIdentity()
	{
		return *this == identity();
	}

	SIRENITO_API Quaternion rotation()
	{
		Quaternion q = Quaternion::identity();
		MY4X4 m = MY4X4(GetColumn(0), GetColumn(1), GetColumn(2), GetColumn(3));
		Vector3 scale = GetlossyScale();

		float m00 = *GetPointerAt(0, 0) /= scale.x;
		float m01 = *GetPointerAt(0, 1) /= scale.y;
		float m02 = *GetPointerAt(0, 2) /= scale.z;
		float m10 = *GetPointerAt(1, 0) /= scale.x;
		float m11 = *GetPointerAt(1, 1) /= scale.y;
		float m12 = *GetPointerAt(1, 2) /= scale.z;
		float m20 = *GetPointerAt(2, 0) /= scale.x;
		float m21 = *GetPointerAt(2, 1) /= scale.y;
		float m22 = *GetPointerAt(2, 2) /= scale.z;

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
	//     The determinant of the matrix. (Read Only)
	SIRENITO_API float GetDeterminant()
	{
		return Determinant(*this);
	}

	//
	// Summary:
	//     Returns the transpose of this matrix (Read Only).
	SIRENITO_API MY4X4 GetTranspose()
	{
		return Transpose(*this);
	}


	//
	// Summary:
	//     The inverse of this matrix. (Read Only)
	SIRENITO_API MY4X4 GetInverse()
	{
		return Inverse(*this);
	}

#pragma endregion 

#pragma region  Constructors

	SIRENITO_API MY4X4()
	{
		m00 = 1.0f;
		m10 = 0.0f;
		m20 = 0.0f;
		m30 = 0.0f;

		m01 = 0.0f;
		m11 = 1.0f;
		m21 = 0.0f;
		m31 = 0.0f;

		m02 = 0.0f;
		m12 = 0.0f;
		m22 = 1.0f;
		m32 = 0.0f;

		m03 = 0.0f;
		m13 = 0.0f;
		m23 = 0.0f;
		m33 = 1.0f;
	}
	SIRENITO_API MY4X4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3)
	{
		m00 = column0.x;
		m10 = column0.y;
		m20 = column0.z;
		m30 = column0.w;

		m01 = column1.x;
		m11 = column1.y;
		m21 = column1.z;
		m31 = column1.w;

		m02 = column2.x;
		m12 = column2.y;
		m22 = column2.z;
		m32 = column2.w;

		m03 = column3.x;
		m13 = column3.y;
		m23 = column3.z;
		m33 = column3.w;
	}

#pragma endregion 

#pragma region  Defaults

	//
	// Summary:
	//     Returns a matrix with all elements set to zero (Read Only).
	SIRENITO_API static MY4X4 zero()
	{
		return MY4X4(Vector4::zero(), Vector4::zero(), Vector4::zero(), Vector4::zero());
	}


	//
	// Summary:
	//     Returns the identity matrix (Read Only).
	SIRENITO_API static MY4X4 identity()
	{
		Vector4 col1 = Vector4(1, 0);
		Vector4 col2 = Vector4(0, 1);
		Vector4 col3 = Vector4(0, 0, 1);
		Vector4 col4 = Vector4(0, 0, 0, 1);
		return MY4X4(col1, col2, col3, col4);
	}

#pragma endregion 

#pragma region  Operators

	SIRENITO_API Vector4 operator *(Vector4 vector)
	{
		//each row times column (in this case always same column vector)
		float x = this->m00 * vector.x + this->m01 * vector.y + this->m02 * vector.z + this->m03 * vector.w;
		float y = this->m10 * vector.x + this->m11 * vector.y + this->m12 * vector.z + this->m13 * vector.w;
		float z = this->m20 * vector.x + this->m21 * vector.y + this->m22 * vector.z + this->m23 * vector.w;

		return Vector4(x, y, z, vector.w);
	}

	SIRENITO_API MY4X4 operator *(MY4X4 rhs)
	{
		MY4X4 newMatrix = MY4X4::zero();
		newMatrix.m00 = this->m00 * rhs.m00 + this->m01 * rhs.m10 + this->m02 * rhs.m20 + this->m03 * rhs.m30;
		newMatrix.m01 = this->m00 * rhs.m01 + this->m01 * rhs.m11 + this->m02 * rhs.m21 + this->m03 * rhs.m31;
		newMatrix.m02 = this->m00 * rhs.m02 + this->m01 * rhs.m12 + this->m02 * rhs.m22 + this->m03 * rhs.m32;
		newMatrix.m03 = this->m00 * rhs.m03 + this->m01 * rhs.m13 + this->m02 * rhs.m23 + this->m03 * rhs.m33;

		newMatrix.m10 = this->m10 * rhs.m00 + this->m11 * rhs.m10 + this->m12 * rhs.m20 + this->m13 * rhs.m30;
		newMatrix.m11 = this->m10 * rhs.m01 + this->m11 * rhs.m11 + this->m12 * rhs.m21 + this->m13 * rhs.m31;
		newMatrix.m12 = this->m10 * rhs.m02 + this->m11 * rhs.m12 + this->m12 * rhs.m22 + this->m13 * rhs.m32;
		newMatrix.m13 = this->m10 * rhs.m03 + this->m11 * rhs.m13 + this->m12 * rhs.m23 + this->m13 * rhs.m33;

		newMatrix.m20 = this->m20 * rhs.m00 + this->m21 * rhs.m10 + this->m22 * rhs.m20 + this->m23 * rhs.m30;
		newMatrix.m21 = this->m20 * rhs.m01 + this->m21 * rhs.m11 + this->m22 * rhs.m21 + this->m23 * rhs.m31;
		newMatrix.m22 = this->m20 * rhs.m02 + this->m21 * rhs.m12 + this->m22 * rhs.m22 + this->m23 * rhs.m32;
		newMatrix.m23 = this->m20 * rhs.m03 + this->m21 * rhs.m13 + this->m22 * rhs.m23 + this->m23 * rhs.m33;

		newMatrix.m30 = this->m30 * rhs.m00 + this->m31 * rhs.m10 + this->m32 * rhs.m20 + this->m33 * rhs.m30;
		newMatrix.m31 = this->m30 * rhs.m01 + this->m31 * rhs.m11 + this->m32 * rhs.m21 + this->m33 * rhs.m31;
		newMatrix.m32 = this->m30 * rhs.m02 + this->m31 * rhs.m12 + this->m32 * rhs.m22 + this->m33 * rhs.m32;
		newMatrix.m33 = this->m30 * rhs.m03 + this->m31 * rhs.m13 + this->m32 * rhs.m23 + this->m33 * rhs.m33;

		return newMatrix;
	}
	SIRENITO_API void operator *=(MY4X4 rhs)
	{
		*this = *this * rhs;
	}

	SIRENITO_API bool operator ==(MY4X4 rhs)
	{
		float kEpsilon = 1E-25F;

		float diff_m00 = this->m00 - rhs.m00;
		float diff_m01 = this->m01 - rhs.m01;
		float diff_m02 = this->m02 - rhs.m02;
		float diff_m03 = this->m03 - rhs.m03;

		float sqrRow0 = diff_m00 * diff_m00 + diff_m01 * diff_m01 + diff_m02 * diff_m02 + diff_m03 * diff_m03;

		float diff_m10 = this->m10 - rhs.m10;
		float diff_m11 = this->m11 - rhs.m11;
		float diff_m12 = this->m12 - rhs.m12;
		float diff_m13 = this->m13 - rhs.m13;
		float sqrRow1 = diff_m10 * diff_m10 + diff_m11 * diff_m11 + diff_m12 * diff_m12 + diff_m13 * diff_m13;

		float diff_m20 = this->m20 - rhs.m20;
		float diff_m21 = this->m21 - rhs.m21;
		float diff_m22 = this->m22 - rhs.m22;
		float diff_m23 = this->m23 - rhs.m23;
		float sqrRow2 = diff_m20 * diff_m20 + diff_m21 * diff_m21 + diff_m22 * diff_m22 + diff_m23 * diff_m23;

		float diff_m30 = this->m30 - rhs.m30;
		float diff_m31 = this->m31 - rhs.m31;
		float diff_m32 = this->m32 - rhs.m32;
		float diff_m33 = this->m33 - rhs.m33;
		float sqrRow3 = diff_m30 * diff_m30 + diff_m31 * diff_m31 + diff_m32 * diff_m32 + diff_m33 * diff_m33;

		float squares = sqrRow0 + sqrRow1 + sqrRow2 + sqrRow3;
		return squares < kEpsilon * kEpsilon;
		//Checks if the difference between both vectors is close to zero
		// return sqrmag < kEpsilon * kEpsilon;
	}

	SIRENITO_API bool operator !=(MY4X4 rhs)
	{
		return !(*this == rhs);
	}

#pragma endregion 

#pragma region  Functions

	SIRENITO_API static MY4X4 TRS(Vector3 pos, Quaternion q, Vector3 s)
	{
		return Translate(pos) * Rotate(q) * Scale(s);
	}

	SIRENITO_API static float Determinant(MY4X4 m)
	{
		float a = m.m00;
		float b = m.m01;
		float c = m.m02;
		float d = m.m03;

		//m00 m01 m02 m03
		//m10 m11 m12 m13
		//m20 m21 m22 m23
		//m30 m31 m32 m33

		// aDeterminant 
		// m11 m12 m13
		// m21 m22 m23
		// m31 m32 m33
		float aDeterminant = m.m11 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) + m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);

		// bDeterminant 
		// m10 m12 m13
		// m20 m22 m23
		// m30 m32 m33
		float bDeterminant = m.m10 * (m.m22 * m.m33 - m.m23 * m.m32) - m.m12 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m32 - m.m22 * m.m30);

		// cDeterminant 
		// m10 m11 m13
		// m20 m21 m23
		// m30 m31 m33
		float cDeterminant = m.m10 * (m.m21 * m.m33 - m.m23 * m.m31) - m.m11 * (m.m20 * m.m33 - m.m23 * m.m30) + m.m13 * (m.m20 * m.m31 - m.m21 * m.m30);

		// dDeterminant 
		// m10 m11 m12
		// m20 m21 m22
		// m30 m31 m32
		float dDeterminant = m.m10 * (m.m21 * m.m32 - m.m22 * m.m31) - m.m11 * (m.m20 * m.m32 - m.m22 * m.m30) + m.m12 * (m.m20 * m.m31 - m.m21 * m.m30);

		return a * aDeterminant - b * bDeterminant + c * cDeterminant - d * dDeterminant;
	}

	SIRENITO_API static MY4X4 Inverse(MY4X4 m)
	{
		float detA = Determinant(m); //Debe tener determinante, de otra forma, no es inversible
		if (detA == 0)
			return zero();

		Vector4 row0;
		Vector4 row1;
		Vector4 row2;
		Vector4 row3;

#pragma region  Row0

		float m00determine = m.m11 * m.m22 * m.m33 + m.m12 * m.m23 * m.m31 + m.m13 * m.m21 * m.m32 - m.m11 * m.m23 * m.m32 - m.m12 * m.m21 * m.m33 - m.m13 * m.m22 * m.m31;
		float m01determine = m.m01 * m.m23 * m.m32 + m.m02 * m.m21 * m.m33 + m.m03 * m.m22 * m.m31 - m.m01 * m.m22 * m.m33 - m.m02 * m.m23 * m.m31 - m.m03 * m.m21 * m.m32;
		float m02determine = m.m01 * m.m12 * m.m33 + m.m02 * m.m13 * m.m32 + m.m03 * m.m11 * m.m32 - m.m01 * m.m13 * m.m32 - m.m02 * m.m11 * m.m33 - m.m03 * m.m12 * m.m31;
		float m03determine = m.m01 * m.m13 * m.m22 + m.m02 * m.m11 * m.m23 + m.m03 * m.m12 * m.m21 - m.m01 * m.m12 * m.m23 - m.m02 * m.m13 * m.m21 - m.m03 * m.m11 * m.m22;
		row0 = Vector4(m00determine, m01determine, m02determine, m03determine);

#pragma endregion 

#pragma region  Row1

		float m10determine = m.m10 * m.m23 * m.m32 + m.m12 * m.m20 * m.m33 + m.m13 * m.m22 * m.m30 - m.m10 * m.m22 * m.m33 - m.m12 * m.m23 * m.m30 - m.m13 * m.m20 * m.m32;
		float m11determine = m.m00 * m.m22 * m.m33 + m.m02 * m.m23 * m.m30 + m.m03 * m.m20 * m.m32 - m.m00 * m.m23 * m.m32 - m.m02 * m.m20 * m.m33 - m.m03 * m.m22 * m.m30;
		float m12determine = m.m00 * m.m13 * m.m32 + m.m02 * m.m10 * m.m33 + m.m03 * m.m12 * m.m30 - m.m00 * m.m12 * m.m33 - m.m02 * m.m13 * m.m30 - m.m03 * m.m10 * m.m32;
		float m13determine = m.m00 * m.m12 * m.m23 + m.m02 * m.m13 * m.m20 + m.m03 * m.m10 * m.m22 - m.m00 * m.m13 * m.m22 - m.m02 * m.m10 * m.m23 - m.m03 * m.m12 * m.m20;
		row1 = Vector4(m10determine, m11determine, m12determine, m13determine);

#pragma endregion 

#pragma region  Row2

		float m20determine = m.m10 * m.m21 * m.m33 + m.m11 * m.m23 * m.m30 + m.m13 * m.m20 * m.m31 - m.m10 * m.m23 * m.m31 - m.m11 * m.m20 * m.m33 - m.m13 * m.m31 * m.m30;
		float m21determine = m.m00 * m.m23 * m.m31 + m.m01 * m.m20 * m.m33 + m.m03 * m.m21 * m.m30 - m.m00 * m.m21 * m.m33 - m.m01 * m.m23 * m.m30 - m.m03 * m.m20 * m.m31;
		float m22determine = m.m00 * m.m11 * m.m33 + m.m01 * m.m13 * m.m31 + m.m03 * m.m10 * m.m31 - m.m00 * m.m13 * m.m31 - m.m01 * m.m10 * m.m33 - m.m03 * m.m11 * m.m30;
		float m23determine = m.m00 * m.m13 * m.m21 + m.m01 * m.m10 * m.m23 + m.m03 * m.m11 * m.m31 - m.m00 * m.m11 * m.m23 - m.m01 * m.m13 * m.m20 - m.m03 * m.m10 * m.m21;
		row2 = Vector4(m20determine, m21determine, m22determine, m23determine);

#pragma endregion 

#pragma region  Row3

		float m30determine = m.m10 * m.m22 * m.m31 + m.m11 * m.m20 * m.m32 + m.m12 * m.m21 * m.m30 - m.m00 * m.m21 * m.m32 - m.m11 * m.m22 * m.m30 - m.m12 * m.m20 * m.m31;
		float m31determine = m.m00 * m.m21 * m.m32 + m.m01 * m.m22 * m.m30 + m.m02 * m.m20 * m.m31 - m.m00 * m.m22 * m.m31 - m.m01 * m.m20 * m.m32 - m.m02 * m.m21 * m.m30;
		float m32determine = m.m00 * m.m12 * m.m31 + m.m01 * m.m10 * m.m32 + m.m02 * m.m11 * m.m30 - m.m00 * m.m11 * m.m32 - m.m01 * m.m12 * m.m30 - m.m02 * m.m10 * m.m31;
		float m33determine = m.m00 * m.m11 * m.m22 + m.m01 * m.m12 * m.m20 + m.m02 * m.m10 * m.m21 - m.m00 * m.m12 * m.m21 - m.m01 * m.m10 * m.m22 - m.m02 * m.m11 * m.m20;
		row3 = Vector4(m30determine, m31determine, m32determine, m33determine);

#pragma endregion 

		row0 /= detA;
		row1 /= detA;
		row2 /= detA;
		row3 /= detA;

		MY4X4 res = MY4X4::identity();

		res.SetRow(0, row0);
		res.SetRow(1, row1);
		res.SetRow(2, row2);
		res.SetRow(3, row3);

		return res;
	}

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
	//     Creates a scaling matrix.
	//
	// Parameters:
	//   vector:
	SIRENITO_API static MY4X4 Scale(Vector3 vector)
	{
		Vector4 col1 = Vector4(vector.x, 0);
		Vector4 col2 = Vector4(0, vector.y);
		Vector4 col3 = Vector4(0, 0, vector.z);
		Vector4 col4 = Vector4(0, 0, 0, 1);
		return MY4X4(col1, col2, col3, col4);
	}

	//
	// Summary:
	//     Creates a translation matrix.
	//
	// Parameters:
	//   vector:
	SIRENITO_API static MY4X4 Translate(Vector3 vector)
	{
		Vector4 col1 = Vector4(1, 0);
		Vector4 col2 = Vector4(0, 1);
		Vector4 col3 = Vector4(0, 0, 1);
		Vector4 col4 = Vector4(vector.x, vector.y, vector.z, 1);
		return MY4X4(col1, col2, col3, col4);
	}

	SIRENITO_API static MY4X4 Transpose(MY4X4 m)
	{
		Vector4 row0 = m.GetRow(0);
		Vector4 row1 = m.GetRow(1);
		Vector4 row2 = m.GetRow(2);
		Vector4 row3 = m.GetRow(3);

		return MY4X4(row0, row1, row2, row3);
	}

	SIRENITO_API static MY4X4 LookAt(Vector3 from, Vector3 to, Vector3 up)
	{
		return TRS(from, Quaternion::LookRotation(to - from, up), Vector3::One());
	}

	//
	// Summary:
	//     Get a column of the matrix.
	//
	// Parameters:
	//   index:
	SIRENITO_API Vector4 GetColumn(int index)
	{
		switch (index)
		{
		case 0:
			return Vector4(m00, m10, m20, m30);
		case 1:
			return Vector4(m01, m11, m21, m31);
		case 2:
			return Vector4(m02, m12, m22, m32);
		case 3:
			return Vector4(m03, m13, m23, m33);
		}
	}

	//
	// Summary:
	//     Get position vector from the matrix.
	SIRENITO_API Vector3 GetPosition()
	{
		return Vector3(m03, m13, m23);
	}

	//
	// Summary:
	//     Returns a row of the matrix.
	//
	// Parameters:
	//   index:
	SIRENITO_API Vector4 GetRow(int index)
	{
		switch (index)
		{
		case 0:
			return Vector4(m00, m01, m02, m03);
		case 1:
			return Vector4(m10, m11, m12, m13);
		case 2:
			return Vector4(m20, m21, m22, m23);
		case 3:
			return Vector4(m30, m31, m32, m33);
		}
	}

	//
	// Summary:
	//     Transforms a position by this matrix (generic).
	//
	// Parameters:
	//   point:
	SIRENITO_API Vector3 MultiplyPoint(Vector3 point)
	{
		Vector4 v4Point = Vector4(point.x, point.y, point.z, 1);
		v4Point = *this * v4Point;

		return  Vector3(v4Point.x, v4Point.y, v4Point.z);
	}

	//
	// Summary:
	//     Transforms a position by this matrix (fast).
	//
	// Parameters:
	//   point:
	SIRENITO_API Vector3 MultiplyPoint3x4(Vector3 point)
	{
		Vector3 res;
		res.x = (m00 * point.x + m01 * point.y + m02 * point.z) + m03;
		res.y = (m10 * point.x + m11 * point.y + m12 * point.z) + m13;
		res.z = (m20 * point.x + m21 * point.y + m22 * point.z) + m23;
		return res;
	}

	//
	// Summary:
	//     Transforms a direction by this matrix.
	//
	// Parameters:
	//   vector:
	SIRENITO_API Vector3 MultiplyVector(Vector3 vector)
	{
		Vector3 res = Vector3();
		res.x = m00 * vector.x + m01 * vector.y + m02 * vector.z;
		res.y = m10 * vector.x + m11 * vector.y + m12 * vector.z;
		res.z = m20 * vector.x + m21 * vector.y + m22 * vector.z;
		return res;
	}

	//
	// Summary:
	//     Sets a column of the matrix.
	//
	// Parameters:
	//   index:
	//
	//   column:
	SIRENITO_API void SetColumn(int index, Vector4 column)
	{
		*GetPointerAt(0, index) = column.x;
		*GetPointerAt(1, index) = column.y;
		*GetPointerAt(2, index) = column.z;
		*GetPointerAt(3, index) = column.w;
	}

	//
	// Summary:
	//     Sets a row of the matrix.
	//
	// Parameters:
	//   index:
	//
	//   row:
	SIRENITO_API void SetRow(int index, Vector4 row)
	{
		*GetPointerAt(index, 0) = row.x;
		*GetPointerAt(index, 1) = row.y;
		*GetPointerAt(index, 2) = row.z;
		*GetPointerAt(index, 3) = row.w;
	}

	SIRENITO_API void SetTRS(Vector3 pos, Quaternion q, Vector3 s)
	{
		MY4X4 transform = TRS(pos, q, s);

		for (int i = 0; i < 4; i++)
		{
			SetColumn(i, transform.GetColumn(i));
		}
	}

	//
	// Summary:
	//     Checks if this matrix is a valid transform matrix.
	SIRENITO_API bool ValidTRS()
	{
		//Checks if every axis is orthogonal (aka everyone of them are perpendicular between them)

		Vector3 column0 = Vector3(m00, m10, m20);
		Vector3 column1 = Vector3(m01, m11, m21);
		Vector3 column2 = Vector3(m02, m12, m22);

		return Vector3::Dot(column0, column1) <= KEpsilon &&
			Vector3::Dot(column0, column2) <= KEpsilon &&
			Vector3::Dot(column1, column2) <= KEpsilon;
	}

#pragma endregion

#pragma region Internals

	SIRENITO_API float* GetPointerAt(int index)
	{
		float* values[] = { &m00, &m01, &m02, &m03, &m10, &m11, &m12, &m13, &m20, &m21, &m22, &m23, &m30, &m31, &m32, &m33 };
		return values[index];
	}
	SIRENITO_API float* GetPointerAt(int row, int column)
	{
		return GetPointerAt(column + row * 4);
	}


	SIRENITO_API void SetValueAt(int index, float value)
	{
		float values[] = { m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 };
		values[index] = value;

		m00 = values[0];
		m01 = values[1];
		m02 = values[2];
		m03 = values[3];
		m10 = values[4];
		m11 = values[5];
		m12 = values[6];
		m13 = values[7];
		m20 = values[8];
		m21 = values[9];
		m22 = values[10];
		m23 = values[11];
		m30 = values[12];
		m31 = values[13];
		m32 = values[14];
		m33 = values[15];
	}

	SIRENITO_API void SetValueAt(int row, int column, float value)
	{
		SetValueAt(column + row * 4, value);
	}

	SIRENITO_API glm::mat4 ToGlm()
	{
		return glm::mat4(GetColumn(0).ToGlm(), GetColumn(1).ToGlm(), GetColumn(2).ToGlm(), GetColumn(3).ToGlm());
	}
	SIRENITO_API static MY4X4 FromGlm(glm::mat4 mat)
	{
		return MY4X4(Vector4(mat[0].x, mat[0].y, mat[0].z, mat[0].w),
			Vector4(mat[1].x, mat[1].y, mat[1].z, mat[1].w),
			Vector4(mat[2].x, mat[2].y, mat[2].z, mat[2].w),
			Vector4(mat[3].x, mat[3].y, mat[3].z, mat[3].w));
	}
#pragma endregion
};
