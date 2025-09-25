#pragma once
#include "Exporter.h"
#include "Vector3.h"

SIRENITO_API class Self_Plane
{

#pragma region Variables

private:
	Vector3 normal;
	float distance;

public:

	Vector3 GetNormal()
	{
		return normal.normalized();
	}

	float GetDistance()
	{
		return distance;
	}

	Self_Plane GetFlipped()
	{
		return Self_Plane(normal * -1, -distance);
	}

#pragma endregion

#pragma region Constructors

	Self_Plane(Vector3 inNormal, Vector3 inPoint)
	{
		normal = inNormal;
		distance = Vector3::Dot(inNormal, inPoint) / normal.magnitude();
	}
	Self_Plane(vector<Vertex> vertices)
	{
		Vector3 avgPos = Vector3::Zero();
		Vector3 inNormal = Vector3::Zero();

		for (int i = 0; i < vertices.size(); i++)
		{
			if (i == 0)
				inNormal = Vector3(vertices[i].Normal.x, vertices[i].Normal.y, vertices[i].Normal.z);

			avgPos = avgPos + Vector3(vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
		}
		avgPos /= vertices.size();

		normal = inNormal.normalized();
		distance = Vector3::Dot(normal, avgPos) / normal.magnitude();
	}

	Self_Plane(Vector3 inNormal, float d)
	{
		normal = inNormal;
		distance = d;
	}

	Self_Plane(Vector3 a, Vector3 b, Vector3 c)
	{
		//https://math.stackexchange.com/questions/1034568/find-the-plane-a-triangle-lies-on
		normal = Vector3::Cross(b - a, c - a);
		Vector3 triangleCenter = (a + b + c) / 3;
		distance = Vector3::Dot(normal, triangleCenter) / -normal.magnitude();
	}

#pragma endregion

#pragma region Functions

	static Self_Plane Translate(Self_Plane plane, Vector3 translation)
	{
		float newPlaneDistance = plane.distance + Vector3::Dot(plane.normal, translation) / plane.normal.magnitude();
		return Self_Plane(plane.normal, newPlaneDistance);
	}

	Vector3 ClosestPointOnPlane(Vector3 point)
	{
		Vector3 normalizedNormal = normal.normalized();

		float t = GetDistanceToPoint(point) / -Vector3::Dot(normalizedNormal, normalizedNormal);
		return Vector3(normalizedNormal.x * t + point.x, normalizedNormal.y * t + point.y, normalizedNormal.z * t + point.z);
	}

	void Flip()
	{
		normal *= -1;
		distance *= -1;
	}

	float GetDistanceToPoint(Vector3 point)
	{
		return (Vector3::Dot(normal, point) + (distance * normal.magnitude())) / normal.magnitude();
	}

	bool GetSide(Vector3 point)
	{
		return Vector3::Dot(normal, (point - (normal * distance))) > 0;
	}

	bool SameSide(Vector3 inPt0, Vector3 inPt1)
	{
		return GetSide(inPt0) == GetSide(inPt1);
	}

	void Set3Points(Vector3 a, Vector3 b, Vector3 c)
	{
		normal = Vector3::Cross(b - a, c - a);
		Vector3 triangleCenter = (a + b + c) / 3;
		distance = Vector3::Dot(normal, triangleCenter) / -normal.magnitude();
	}

	void SetNormalAndPosition(Vector3 inNormal, Vector3 inPoint)
	{
		normal = inNormal;
		distance = Vector3::Dot(inNormal, inPoint) / -normal.magnitude();
	}

	void Translate(Vector3 translation)
	{
		distance += Vector3::Dot(normal, translation) / normal.magnitude();
	}
#pragma endregion

};