#include "Entity/Entity3D/Model.h"
#include "AssetImporter/AssetImporter.h"

Model::Model(const char* path, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	meshes = AssetImporter::GetMeshes(path, Material(), rendererInstance);

	transform = new Transform();
}
Model::Model(const char* path, Material material, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	meshes = AssetImporter::GetMeshes(path, material, rendererInstance);

	transform = new Transform();
}

Model::~Model()
{
	if (meshes != nullptr)
		delete meshes;

	delete transform;
}

void Model::Draw()
{
	for (int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i).transform = this->transform;
		meshes->at(i).Draw();
		meshes->at(i).transform = nullptr;
	}
}
