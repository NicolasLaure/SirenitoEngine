#include "Entity/Entity3D/Model.h"
#include "AssetImporter/AssetImporter.h"
#include "Textures/Importer/TextureImporter.h"

#include <iostream>

void Model::PopulateChildren()
{
	for (int i = 0; i < transform->ChildCount(); i++)
	{
		vector<Mesh*>* childrenMeshes = new vector<Mesh*>();
		for (int j = 0; j < meshes->size(); j++)
		{
			if (meshes->at(j)->transform->IsChildOf(transform->GetChild(i)))
				childrenMeshes->push_back(meshes->at(j));
		}

		if (boundingBox != nullptr)
			children.push_back(new Model(childrenMeshes, transform->GetChild(i), boundingBox->GetChild(transform->GetChild(i))));
		else
			children.push_back(new Model(childrenMeshes, transform->GetChild(i), nullptr));
	}
}

Model::Model(vector<Mesh*>* meshes, Transform* transform, BoundingBox* boundingBox)
{
	this->meshes = meshes;
	this->transform = transform;
	this->boundingBox = boundingBox;
	PopulateChildren();
}

Model::Model(const char* path, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	transform = new Transform("Model");

	boundingBox = new BoundingBox(transform, rendererInstance);
	meshes = AssetImporter::GetMeshes(path, transform, boundingBox, Material(), rendererInstance);
	PopulateChildren();
}
Model::Model(const char* path, Material material, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	transform = new Transform("Model");

	boundingBox = new BoundingBox(transform, rendererInstance);
	meshes = AssetImporter::GetMeshes(path, transform, boundingBox, material, rendererInstance);
	PopulateChildren();
}

Model::~Model()
{
	delete boundingBox;
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
	if (boundingBox != nullptr)
	{
		boundingBox->CalculateCompoundBoundingBox();
		boundingBox->Draw();
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
