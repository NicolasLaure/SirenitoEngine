#pragma once

#include <vector>
#include "Utilities/Exporter.h"
#include "Utilities/Vector3.h"
#include "Utilities/Transform.h"
#include "Entity/Entity3D/Cube.h"

using namespace std;

SIRENITO_API class Frustum
{
private:
	int screenWidth;
	int screenHeight;

	float fieldOfViewAngle;
	float verticalfieldOfViewAngle;
	float nearClippingPlane;
	float renderingDistance;

	float aspectRatio;
	// Start is called before the first frame update

	Vector3 farLimit;
	Vector3 nearLimit;

	Transform* cameraTransform;
public:

	Vector3 nearUpperLeftVertex;
	Vector3 nearUpperRightVertex;
	Vector3 nearLowerLeftVertex;
	Vector3 nearLowerRightVertex;

	Vector3 farUpperLeftVertex;
	Vector3 farUpperRightVertex;
	Vector3 farLowerLeftVertex;
	Vector3 farLowerRightVertex;

	int vertexCount = 18;
	Vector3* vertices = nullptr;
	Cube* debugCubes = nullptr;

	SIRENITO_API Frustum(int screenWidth, int  screenHeight, float fovAngle, float nearDistance, float renderDistance, Transform* cameraTransform);
	SIRENITO_API ~Frustum();
	SIRENITO_API void Update();
	SIRENITO_API void UpdateVertices();

	SIRENITO_API void AddDebugCubes(Renderer* rendererInstance);
	SIRENITO_API void Draw();
	SIRENITO_API Vector3 GetFaceNormal(int index);

	SIRENITO_API bool IsPointInside(Vector3 point);
	SIRENITO_API bool IsPointInside(Vector3 point, int faceIndex);

	SIRENITO_API Vector3 GetFacePoint(int faceIndex);
};