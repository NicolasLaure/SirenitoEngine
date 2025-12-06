#include "Frustum/Frustum.h"
#include <iostream>

Frustum::Frustum(int screenWidth, int screenHeight, float fovAngle, float nearDistance, float renderDistance, Transform* transform)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	fieldOfViewAngle = fovAngle;
	nearClippingPlane = nearDistance;
	renderingDistance = renderDistance;
	cameraTransform = transform;

	vertices = new Vector3[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i] = Vector3::Zero();
	}
}

Frustum::~Frustum()
{
	delete[] debugCubes;
	delete[] vertices;
}

void Frustum::AddDebugCubes(Renderer* rendererInstance)
{
	debugCubes = new Cube[8];

	for (int i = 0; i < 8; i++)
	{
		debugCubes[i].SetRendererInstance(rendererInstance);
		if (i < 4)
			debugCubes[i].transform->SetLocalScale(Vector3(0.1f, 0.1f, 0.1f));
		else
			debugCubes[i].transform->SetLocalScale(Vector3(1.5f, 1.5f, 1.5f));
	}
}

void Frustum::Draw()
{
	if (debugCubes == nullptr)
		return;

	debugCubes[0].transform->SetPosition(nearLowerLeftVertex);
	debugCubes[1].transform->SetPosition(nearLowerRightVertex);
	debugCubes[2].transform->SetPosition(nearUpperLeftVertex);
	debugCubes[3].transform->SetPosition(nearUpperRightVertex);

	debugCubes[4].transform->SetPosition(farLowerLeftVertex);
	debugCubes[5].transform->SetPosition(farLowerRightVertex);
	debugCubes[6].transform->SetPosition(farUpperLeftVertex);
	debugCubes[7].transform->SetPosition(farUpperRightVertex);

	for (int i = 0; i < 8; i++)
	{
		debugCubes[i].Draw();
	}
}


void Frustum::Update()
{
	aspectRatio = (float)screenWidth / (float)screenHeight;

	verticalfieldOfViewAngle = fieldOfViewAngle / aspectRatio;

	Vector3 fwd = cameraTransform->GetForward().normalized();
	Vector3 up = cameraTransform->GetUp().normalized();
	Vector3 right = cameraTransform->GetRight().normalized();

	nearLimit = cameraTransform->GetPosition() + (fwd * nearClippingPlane);
	farLimit = cameraTransform->GetPosition() + (fwd * renderingDistance);

	float nearPlaneHalfWidth = tan((fieldOfViewAngle / 2) * Deg2Rad) * nearClippingPlane;
	float nearPlaneHalfHeight = tan((verticalfieldOfViewAngle / 2) * Deg2Rad) * nearClippingPlane;

	float farPlaneHalfWidth = tan((fieldOfViewAngle / 2) * Deg2Rad) * renderingDistance;
	float farPlaneHalfHeight = tan((verticalfieldOfViewAngle / 2) * Deg2Rad) * renderingDistance;

	// up and Right are the current direction of the local axes of the cameraTransform, this means, that it takes in account the current rotation of the object.

	// all four fixed Centers reference the local position (towards the object cameraTransform, and more specifically it's current rotation) that represent the center of the planes.
	Vector3 fixedNearCenterX = right * nearPlaneHalfWidth;
	Vector3 fixedNearCenterY = up * nearPlaneHalfHeight;

	Vector3 fixedFarCenterX = right * farPlaneHalfWidth;
	Vector3 fixedFarCenterY = up * farPlaneHalfHeight;

	// Calculations needed to obtain each vertex of the planes
	nearUpperLeftVertex = nearLimit - fixedNearCenterX + fixedNearCenterY;
	nearUpperRightVertex = nearLimit + fixedNearCenterX + fixedNearCenterY;
	nearLowerLeftVertex = nearLimit - fixedNearCenterX - fixedNearCenterY;
	nearLowerRightVertex = nearLimit + fixedNearCenterX - fixedNearCenterY;

	farUpperLeftVertex = farLimit - fixedFarCenterX + fixedFarCenterY;
	farUpperRightVertex = farLimit + fixedFarCenterX + fixedFarCenterY;
	farLowerLeftVertex = farLimit - fixedFarCenterX - fixedFarCenterY;
	farLowerRightVertex = farLimit + fixedFarCenterX - fixedFarCenterY;

	UpdateVertices();
}


void Frustum::UpdateVertices()
{
	vertices[0] = cameraTransform->GetPosition();
	vertices[1] = farLowerRightVertex;
	vertices[2] = farLowerLeftVertex;

	vertices[3] = cameraTransform->GetPosition();
	vertices[4] = farUpperLeftVertex;
	vertices[5] = farUpperRightVertex;

	vertices[6] = cameraTransform->GetPosition();
	vertices[7] = farLowerLeftVertex;
	vertices[8] = farUpperLeftVertex;

	vertices[9] = cameraTransform->GetPosition();
	vertices[10] = farUpperRightVertex;
	vertices[11] = farLowerRightVertex;

	vertices[12] = nearUpperLeftVertex;
	vertices[13] = nearUpperRightVertex;
	vertices[14] = nearLowerRightVertex;

	vertices[15] = farUpperLeftVertex;
	vertices[16] = farLowerRightVertex;
	vertices[17] = farUpperRightVertex;
}

Vector3 Frustum::GetFaceNormal(int index)
{
	// https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal#:~:text=A%20surface%20normal%20for%20a,of%20the%20face%20w.r.t.%20winding).
	Vector3 firstVertex = vertices[index * 3];
	Vector3 secondVertex = vertices[(index * 3) + 1];
	Vector3 thirdVertex = vertices[(index * 3) + 2];

	Vector3 normal;
	Vector3 firstSecond = secondVertex - firstVertex;
	Vector3 firstThird = thirdVertex - firstVertex;

	//Vector3 normal = Vector3.zero;
	//Vector3 normal = Vector3.Cross(secondVertex - firstVertex, thirdVertex - firstVertex).normalized;

	normal.x = (firstThird.y * firstSecond.z) - (firstThird.z * firstSecond.y);
	normal.y = (firstThird.z * firstSecond.x) - (firstThird.x * firstSecond.z);
	normal.z = (firstThird.x * firstSecond.y) - (firstThird.y * firstSecond.x);

	return normal.normalized();
}

bool Frustum::IsPointInside(Vector3 point)
{
	for (int i = 0; i < 6; i++)
	{
		if (!IsPointInside(point, i))
			return false;
	}
	return true;
}

bool Frustum::IsPointInside(Vector3 point, int faceIndex)
{
	Vector3 normal = GetFaceNormal(faceIndex);
	Vector3 facePoint = GetFacePoint(faceIndex);
	//Vector3 offset;
	//offset.x = (vertices[faceIndex].x + vertices[faceIndex + 1].x + vertices[faceIndex + 2].x) / 3;
	//offset.y = (vertices[faceIndex].y + vertices[faceIndex + 1].y + vertices[faceIndex + 2].y) / 3;
	//offset.z = (vertices[faceIndex].z + vertices[faceIndex + 1].z + vertices[faceIndex + 2].z) / 3;

	return Vector3::Dot(normal, point - facePoint) > 0;
}

Vector3 Frustum::GetFacePoint(int faceIndex)
{
	Vector3 point;
	point.x = (vertices[faceIndex * 3].x + vertices[(faceIndex * 3) + 1].x + vertices[(faceIndex * 3) + 2].x) / 3;
	point.y = (vertices[faceIndex * 3].y + vertices[(faceIndex * 3) + 1].y + vertices[(faceIndex * 3) + 2].y) / 3;
	point.z = (vertices[faceIndex * 3].z + vertices[(faceIndex * 3) + 1].z + vertices[(faceIndex * 3) + 2].z) / 3;
	return point;
}
