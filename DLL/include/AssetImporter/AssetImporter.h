#pragma once
#include "Utilities/Exporter.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Entity/Entity3D/Mesh.h"
#include "Textures/Texture.h"
#include "Collisions/BoundingBox.h"
#include "Collisions/BSP_scene/Scene.h"

SIRENITO_API static class AssetImporter
{
public:
	SIRENITO_API static vector<Mesh*>* GetMeshes(const char* path, Transform* root, BoundingBox* rootBoundingBox, Material material, Renderer* rendererInstance);
	SIRENITO_API static void ProcessNode(vector<Mesh*>* meshes, Transform* parent, BoundingBox* parentBoundingBox, aiNode* node, const aiScene* scene, Material material, vector<Texture> loadedTextures, string directory, Renderer* rendererInstance);
	SIRENITO_API static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, Material material, vector<Texture> loadedTextures, string directory, Renderer* rendererInstance);
};