#include "Entity/Entity3D/Mesh.h"

Mesh::Mesh(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Color color, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, color, rendererInstance);
}

Mesh::Mesh(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, Color::white(), rendererInstance);
}

Mesh::Mesh(const char* texturePath, float width, float height, Color color, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), width, height, color, rendererInstance);
}

Mesh::Mesh(const char* texturePath, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), width, height, Color::white(), rendererInstance);
}

void Mesh::Init(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Color color, Renderer* rendererInstance)
{
	this->texture = TextureImporter::ImportTexture(texturePath);
	this->width = width;
	this->height = height;

	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	transform = new Transform();
	transform->SetPositionAndRotation(position, Quaternion::Euler(eulers));
	rendererInstance->SetData(transform, color, true, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
}

Mesh::~Mesh()
{
	delete transform;
}

void Mesh::SetTexture(const char* path)
{
	texture = TextureImporter::ImportTexture(path);
}

void Mesh::Draw()
{
	rendererInstance->SetData(transform, color, true, GetVertices(width, height), 324, GetIndices(), 36, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, 36, texture.GetId());
}

float* Mesh::GetVertices(float width, float height)
{
	return GetVertices(width, height, Vector2(0, 0), Vector2(1, 1));
}

float* Mesh::GetVertices(float width, float height, Vector2 minCoords, Vector2 maxCoords)
{
	return new float[324]
		{
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				0.5f, -0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,

				// Front face
				-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,

				// Left face
				-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,

				// Right face
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,

				// Bottom face
				-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				0.5f, -0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,

				// Top face
				-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,
				0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,
				-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,
				-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y
		};
}



unsigned int* Mesh::GetIndices()
{
	return new unsigned int[36]
		{
			0, 1, 2,
				3, 4, 5,
				6, 7, 8,
				9, 10, 11,
				12, 13, 14,
				15, 16, 17,
				18, 19, 20,
				21, 22, 23,
				24, 25, 26,
				27, 28, 29,
				30, 31, 32,
				33, 34, 35
		};
}