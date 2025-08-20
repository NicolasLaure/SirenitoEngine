#include "Entity/Entity3D/Model.h"
#include "AssetImporter/AssetImporter.h"
#include "Textures/Importer/TextureImporter.h"

#include <iostream>

Model::Model(const char* path, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	transform = new Transform("Model");

	meshes = AssetImporter::GetMeshes(path, transform, Material(), rendererInstance);
}
Model::Model(const char* path, Material material, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	transform = new Transform("Model");

	meshes = AssetImporter::GetMeshes(path, transform, material, rendererInstance);
}

Model::~Model()
{
	delete transform;
	transform = nullptr;

	if (meshes != nullptr)
	{
		delete meshes;
		meshes = nullptr;
	}
}

void Model::Draw()
{
	for (int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i)->Draw();
	}
}

void Model::SetTexture(const char* path)
{
	for (int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i)->textures.clear();
		meshes->at(i)->textures.push_back(TextureImporter::ImportTexture(path));
	}
}
