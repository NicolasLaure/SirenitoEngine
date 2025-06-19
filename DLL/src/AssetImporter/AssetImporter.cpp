#include "AssetImporter/AssetImporter.h"
#include <iostream>
#include <string>
#include "Textures/Importer/TextureImporter.h"

using namespace Assimp;

vector<Mesh>* AssetImporter::GetMeshes(const char* path, Material material, Renderer* rendererInstance)
{
	vector<Mesh>* meshes = new vector<Mesh>;
	vector<Texture>* loadedTextures = new vector<Texture>;

	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error::Assimp::" << importer.GetErrorString() << endl;
		system("pause");
		return nullptr;
	}

	string pathString = path;
	string directory = pathString.substr(0, pathString.find_last_of('/') + 1);
	ProcessNode(meshes, scene->mRootNode, scene, material, loadedTextures, directory, rendererInstance);

	return meshes;
}

void AssetImporter::ProcessNode(vector<Mesh>* meshes, aiNode* node, const aiScene* scene, Material material, vector<Texture>* loadedTextures, string directory, Renderer* rendererInstance)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes->push_back(ProcessMesh(mesh, scene, material, loadedTextures, directory, rendererInstance));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(meshes, node->mChildren[i], scene, material, loadedTextures, directory, rendererInstance);
	}
}

Mesh AssetImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, Material material, vector<Texture>* loadedTextures, string directory, Renderer* rendererInstance)
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

		vertices.push_back(vertex);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		aiTextureType type = aiTextureType_DIFFUSE;

		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool shouldAddTexture = true;
			for (int j = 0; j < loadedTextures->size(); j++)
			{
				if (loadedTextures->at(j).name == str.C_Str())
				{
					shouldAddTexture = false;
					textures.push_back(loadedTextures->at(j));
				}
			}

			if (shouldAddTexture)
			{
				Texture texture = TextureImporter::ImportTexture(directory.append(str.C_Str()).c_str());
				texture.name = str.C_Str();
				std::cout << "Texture name: " << texture.name << endl;
				std::cout << "Path: " << directory.append(str.C_Str()).c_str() << endl;
				textures.push_back(texture);
				loadedTextures->push_back(texture);
			}
		}
	}

	return Mesh(vertices, indices, textures, material, rendererInstance);
}
