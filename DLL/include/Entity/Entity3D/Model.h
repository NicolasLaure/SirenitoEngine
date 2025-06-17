#pragma once
#include "Utilities/Exporter.h"
#include "Mesh.h"

SIRENITO_API class Model : public Entity3D
{
protected:
	vector<Mesh>* meshes;

public:
	SIRENITO_API Model(const char* path, Renderer* rendererInstance);
	SIRENITO_API Model(const char* path, Material material, Renderer* rendererInstance);
	SIRENITO_API ~Model();
	SIRENITO_API void Draw();
	SIRENITO_API void SetTexture(const char* path);
};