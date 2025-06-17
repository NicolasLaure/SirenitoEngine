#include "AssetImporter/AssetImporter.h"
#include <iostream>
#include <string>
#include "Textures/Importer/TextureImporter.h"

using namespace Assimp;

vector<Mesh>* AssetImporter::GetMeshes(const char* path, Material material)
{
	vector<Mesh> meshes;

	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error::Assimp::" << importer.GetErrorString() << endl;
		system("pause");
		return nullptr;
	}
	std::cout << "LoadSuccesful";
	system("pause");
	string pathString = path;
	string directory = pathString.substr(0, pathString.find_last_of('/'));
	ProcessNode(&meshes, scene->mRootNode, scene, material, directory);
	return &meshes;
}

void AssetImporter::ProcessNode(vector<Mesh>* meshes, aiNode* node, const aiScene* scene, Material material, string directory)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes->push_back(ProcessMesh(meshes, mesh, scene, material, directory));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(meshes, node->mChildren[i], scene, material, directory);
	}
}

Mesh AssetImporter::ProcessMesh(vector<Mesh>* meshes, aiMesh* mesh, const aiScene* scene, Material material, string directory)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertex.Tint = glm::vec4(1.0f);
		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
	aiTextureType type = aiTextureType_BASE_COLOR;

	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture = TextureImporter::ImportTexture(str.C_Str());
		textures.push_back(texture);
	}
	return Mesh(vertices, indices, textures, material);
}
