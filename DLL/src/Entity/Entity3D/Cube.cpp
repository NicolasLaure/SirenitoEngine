#include "Entity/Entity3D/Cube.h"

Cube::Cube(Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance)
{
	Init(position, eulers, material, rendererInstance);
}

Cube::Cube(const char* texturePath, Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, material, rendererInstance);
}

Cube::Cube(const char* texturePath, Vector3 position, Vector3 eulers, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, Material(), rendererInstance);
}

Cube::Cube(const char* texturePath, Material material, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), material, rendererInstance);
}

Cube::Cube(const char* texturePath, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), Material(), rendererInstance);
}

void Cube::Init(Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();
	this->vertices = GetTransformedVertices();
	this->indices = GetIndices();
	this->material = material;

	transform = new Transform();
	transform->SetPositionAndRotation(position, Quaternion::Euler(eulers));
}

void Cube::Init(const char* texturePath, Vector3 position, Vector3 eulers, Material material, Renderer* rendererInstance)
{
	Init(position, eulers, material, rendererInstance);
	SetTexture(texturePath);
}

Cube::~Cube()
{
	delete transform;
	transform = nullptr;
}

void Cube::SetTexture(const char* path)
{
	textures.clear();
	Texture texture = TextureImporter::ImportTexture(path);
	texture.name = path;
	textures.push_back(texture);
}

vector<Vertex> Cube::GetTransformedVertices()
{
	return GetTransformedVertices(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}

vector<Vertex> Cube::GetTransformedVertices(Vector2 minCoords, Vector2 maxCoords)
{
	vector<Vertex> vertices;
	Vertex vertexArr[36] = {
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f,  0.0f, -1.0f}},
			{{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f,  0.0f, -1.0f}},
			{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f,  0.0f, -1.0f}},
			{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f,  0.0f, -1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f,  0.0f, -1.0f}},
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f,  0.0f, -1.0f}},

			// Front face												     
			{{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f,  0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f,  0.0f, 1.0f}},
			{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f,  0.0f, 1.0f}},
			{{0.5f, 0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f,  0.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f,  0.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f,  0.0f, 1.0f}},

			// Left face												    
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{-1.0f,  0.0f,  0.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{-1.0f,  0.0f,  0.0f}},
			{{-0.5f, -0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{-1.0f,  0.0f,  0.0f}},
			{{-0.5f, -0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{-1.0f,  0.0f,  0.0f}},
			{{-0.5f, -0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{-1.0f,  0.0f,  0.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{-1.0f,  0.0f,  0.0f}},

			// Right face												     
			{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{1.0f,  0.0f,  0.0f}},
			{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{1.0f,  0.0f,  0.0f}},
			{{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{1.0f,  0.0f,  0.0f}},
			{{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{1.0f,  0.0f,  0.0f}},
			{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{1.0f,  0.0f,  0.0f}},
			{{0.5f, 0.5f, 0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{1.0f,  0.0f,  0.0f}},

			// Bottom face												     
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f, -1.0f,  0.0f}},
			{{0.5f, -0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f, -1.0f,  0.0f}},
			{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f, -1.0f,  0.0f}},
			{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f, -1.0f,  0.0f}},
			{{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f, -1.0f,  0.0f}},
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f, -1.0f,  0.0f}},

			// Top face													     
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f,  1.0f,  0.0f}},
			{{0.5f, 0.5f, -0.5f},{1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, maxCoords.y},{0.0f,  1.0f,  0.0f}},
			{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f,  1.0f,  0.0f}},
			{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {maxCoords.x, minCoords.y},{0.0f,  1.0f,  0.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, minCoords.y},{0.0f,  1.0f,  0.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {minCoords.x, maxCoords.y},{0.0f,  1.0f,  0.0f}}
	};
	for (int i = 0; i < 36; i++)
	{
		vertices.push_back(vertexArr[i]);
	}
	return vertices;
}

vector<unsigned int> Cube::GetIndices()
{
	vector<unsigned int> indices;
	unsigned int indexArr[36] = {
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
	for (int i = 0; i < 36; i++)
	{
		indices.push_back(indexArr[i]);
	}
	return indices;
}