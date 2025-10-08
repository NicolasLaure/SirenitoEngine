#pragma once
#include <vector>
#include "Utilities/Vector3.h"
#include "Utilities/Transform.h"
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Cube.h"
using namespace std;

class BoundingBox
{
private:

	Vector3 min;
	Vector3 max;
	Vector3 compoundMin;
	Vector3 compoundMax;

	Transform* transform;
	vector<BoundingBox*> children;
	vector<Vector3>* meshesVertices = nullptr;
	Cube* viewCube = nullptr;
	Renderer* rendererInstance;

	SIRENITO_API void SetCube();
public:
	Vector3 center;
	Vector3 size;

	SIRENITO_API BoundingBox(Transform* transform, Renderer* rendererInstance);
	SIRENITO_API BoundingBox(Transform* transform, vector<Vector3> vertices, Renderer* rendererInstance);
	SIRENITO_API BoundingBox(Transform* transform, vector<BoundingBox*> childrenBoxes, vector<Vector3> vertices, Renderer* rendererInstance);
	SIRENITO_API ~BoundingBox();

	SIRENITO_API void AddChild(BoundingBox* child);
	SIRENITO_API void AddMeshesVertices(vector<Vertex> vertices);

	SIRENITO_API Vector3 GetMin();
	SIRENITO_API Vector3 GetMax();

	SIRENITO_API void CalculateMeshBoundingBox(vector<Vector3> vertexList);
	SIRENITO_API void CalculateMeshBoundingBox(vector<Vertex> vertexList);
	SIRENITO_API void CalculateChildrenMeshesBoundingBox();
	SIRENITO_API void CalculateCompoundBoundingBox();
	SIRENITO_API vector<Vector3> GetCompoundBoundsVertices();
	SIRENITO_API vector<Vector3> GetTransformedBoundsVertices();
	SIRENITO_API void Draw();

	SIRENITO_API BoundingBox* GetChild(Transform* childTransform);
};