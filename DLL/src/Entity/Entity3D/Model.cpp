#include "Entity/Entity3D/Model.h"
#include "AssetImporter/AssetImporter.h"

Model::Model(const char* path, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	vector<Mesh>* meshesPtr = AssetImporter::GetMeshes(path, Material());
	if (meshesPtr != nullptr)
		meshes = *meshesPtr;
}
Model::Model(const char* path, Material material, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	vector<Mesh>* meshesPtr = AssetImporter::GetMeshes(path, Material());
	if (meshesPtr != nullptr)
		meshes = *meshesPtr;
}

void Model::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].SetRendererInstance(rendererInstance);
		meshes[i].Draw();
	}
}
