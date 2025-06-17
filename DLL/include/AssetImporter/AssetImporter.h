#pragma once
#include "Utilities/Exporter.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Entity/Entity3D/Mesh.h"

SIRENITO_API static class AssetImporter
{
public:
	SIRENITO_API static vector<Mesh>* GetMeshes(const char* path, Material material);
	SIRENITO_API static void ProcessNode(vector<Mesh>* meshes, aiNode* node, const aiScene* scene, Material material, string directory);
	SIRENITO_API static Mesh ProcessMesh(vector<Mesh>* meshes, aiMesh* mesh, const aiScene* scene, Material material, string directory);
};