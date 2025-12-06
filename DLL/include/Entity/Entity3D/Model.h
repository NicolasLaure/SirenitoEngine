#pragma once
#include "Utilities/Exporter.h"
#include <map>
#include "Mesh.h"
#include "Collisions/BoundingBox.h"

SIRENITO_API class Model : public Entity3D
{
private:
	SIRENITO_API void PopulateChildren();
public:
	vector<Model*> children;
	vector<Mesh*>* meshes;
	BoundingBox* boundingBox = nullptr;
	bool shouldDraw = true;

	SIRENITO_API Model(vector<Mesh*>* meshes, Transform* transform, BoundingBox* boundingBox);
	SIRENITO_API Model(const char* path, Renderer* rendererInstance);
	SIRENITO_API Model(const char* path, Material material, Renderer* rendererInstance);
	SIRENITO_API ~Model();
	SIRENITO_API void Draw();
	SIRENITO_API void SetTexture(const char* path);
	SIRENITO_API vector<Vector3> GetTransformedVertices();
};