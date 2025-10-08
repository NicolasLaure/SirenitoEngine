#include "AssetImporter/AssetImporter.h"
#include <iostream>
#include <string>
#include "Textures/Importer/TextureImporter.h"

using namespace Assimp;

vector<Mesh*>* AssetImporter::GetMeshes(const char* path, Transform* root, BoundingBox* rootBoundingBox, Material material, Renderer* rendererInstance)
{
	vector<Mesh*>* meshes = new vector<Mesh*>;
	vector<Texture> loadedTextures;

	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error::Assimp::" << importer.GetErrorString() << endl;
		system("pause");
		return nullptr;
	}

	string pathString = path;
	string directory = pathString.substr(0, pathString.find_last_of('/') + 1);
	ProcessNode(meshes, root, rootBoundingBox, scene->mRootNode, scene, material, loadedTextures, directory, rendererInstance);
	return meshes;
}

void AssetImporter::ProcessNode(vector<Mesh*>* meshes, Transform* parent, BoundingBox* parentBoundingBox, aiNode* node, const aiScene* scene, Material material, vector<Texture> loadedTextures, string directory, Renderer* rendererInstance)
{
	for (int i = 0; i < node->mNumChildren; i++)
	{
		Transform* child = new Transform(node->mChildren[i]->mName.C_Str());
		cout << "Parent: " << parent->GetName() << " Has Child: " << child->GetName() << endl;
		child->SetParent(parent);
		parent->AddChild(child);
		aiMatrix4x4 localMatrix = node->mChildren[i]->mTransformation;
		Vector4 col1 = Vector4(localMatrix.a1, localMatrix.b1, localMatrix.c1, localMatrix.d1);
		Vector4 col2 = Vector4(localMatrix.a2, localMatrix.b2, localMatrix.c2, localMatrix.d2);
		Vector4 col3 = Vector4(localMatrix.a3, localMatrix.b3, localMatrix.c3, localMatrix.d3);
		Vector4 col4 = Vector4(localMatrix.a4, localMatrix.b4, localMatrix.c4, localMatrix.d4);
		MY4X4 localM = MY4X4(col1, col2, col3, col4);
		child->SetTRS(localM);
		BoundingBox* childBoundingBox = nullptr;

		if (child->GetName().find("Plane") == string::npos && parentBoundingBox != nullptr)
		{
			childBoundingBox = new BoundingBox(child, rendererInstance);
			parentBoundingBox->AddChild(childBoundingBox);
		}
		ProcessNode(meshes, child, childBoundingBox, node->mChildren[i], scene, material, loadedTextures, directory, rendererInstance);
	}
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* processedMesh = ProcessMesh(mesh, scene, material, loadedTextures, directory, rendererInstance);
		processedMesh->transform->SetParent(parent);
		parent->AddChild(processedMesh->transform);
		if (parentBoundingBox != nullptr)
		{
			BoundingBox* childBoundingBox = new BoundingBox(parent, rendererInstance);
			parentBoundingBox->AddChild(childBoundingBox);
			parentBoundingBox->AddMeshesVertices(processedMesh->vertices);
			childBoundingBox->CalculateMeshBoundingBox(processedMesh->vertices);
		}
		meshes->push_back(processedMesh);
	}
	if (parentBoundingBox != nullptr)
		parentBoundingBox->CalculateChildrenMeshesBoundingBox();
}

Mesh* AssetImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene, Material material, vector<Texture> loadedTextures, string directory, Renderer* rendererInstance)
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
			indices.push_back(face.mIndices[j]);
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
			for (int j = 0; j < loadedTextures.size(); j++)
			{
				if (loadedTextures.at(j).name == str.C_Str())
				{
					shouldAddTexture = false;
					textures.push_back(loadedTextures.at(j));
				}
			}

			if (shouldAddTexture)
			{
				Texture texture = TextureImporter::ImportTexture(directory.append(str.C_Str()).c_str());
				texture.name = str.C_Str();
				textures.push_back(texture);
				loadedTextures.push_back(texture);
			}
		}
	}

	return new Mesh(mesh->mName.C_Str(), vertices, indices, textures, material, rendererInstance);
}
