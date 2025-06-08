#include "Entity/Entity3D/Mesh.h"

Mesh::Mesh(Vector3 position, Vector3 eulers, Color color, Renderer* rendererInstance)
{
	Init(position, eulers, color, rendererInstance);
}

Mesh::Mesh(const char* texturePath, Vector3 position, Vector3 eulers, Color color, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, color, rendererInstance);
}

Mesh::Mesh(const char* texturePath, Vector3 position, Vector3 eulers, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, Color::white(), rendererInstance);
}

Mesh::Mesh(const char* texturePath, Color color, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), color, rendererInstance);
}

Mesh::Mesh(const char* texturePath, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), Color::white(), rendererInstance);
}

void Mesh::Init(Vector3 position, Vector3 eulers, Color color, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	transform = new Transform();
	transform->SetPositionAndRotation(position, Quaternion::Euler(eulers));
}

void Mesh::Init(const char* texturePath, Vector3 position, Vector3 eulers, Color color, Renderer* rendererInstance)
{
	this->texture = TextureImporter::ImportTexture(texturePath);
	Init(position, eulers, color, rendererInstance);
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
	if (texture.GetId() == 0)
	{
		rendererInstance->SetData(transform, color, false, GetVertices(), 360, GetIndices(), 36, VAO, VBO, EBO);
		rendererInstance->Draw(VAO, 36);
	}
	else
	{
		rendererInstance->SetData(transform, color, true, GetVertices(Vector2(0, 0), Vector2(1, 1)), 432, GetIndices(), 36, VAO, VBO, EBO);
		rendererInstance->Draw(VAO, 36, texture.GetId());
	}
}

float* Mesh::GetVertices()
{
	return new float[360]
	{
		-0.5f, -0.5f, -0.5f,      1, 1, 1, 1,    0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,   1, 1, 1, 1,    0.0f,  0.0f, -1.0f,
			0.5f, 0.5f, -0.5f,    1, 1, 1, 1,    0.0f,  0.0f, -1.0f,
			0.5f, 0.5f, -0.5f,    1, 1, 1, 1,    0.0f,  0.0f, -1.0f,
			-0.5f, 0.5f, -0.5f,   1, 1, 1, 1,    0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  1, 1, 1, 1,    0.0f,  0.0f, -1.0f,

			// Front face					    
			-0.5f, -0.5f, 0.5f,   1, 1, 1, 1,    0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, 0.5f,    1, 1, 1, 1,    0.0f,  0.0f, 1.0f,
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    0.0f,  0.0f, 1.0f,
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    0.0f,  0.0f, 1.0f,
			-0.5f, 0.5f, 0.5f,    1, 1, 1, 1,    0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,   1, 1, 1, 1,    0.0f,  0.0f, 1.0f,

			// Left face					   
			-0.5f, 0.5f, 0.5f,    1, 1, 1, 1,  	-1.0f,  0.0f,  0.0f,
			-0.5f, 0.5f, -0.5f,   1, 1, 1, 1, 	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  1, 1, 1, 1,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  1, 1, 1, 1,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, 0.5f,   1, 1, 1, 1, 	-1.0f,  0.0f,  0.0f,
			-0.5f, 0.5f, 0.5f,    1, 1, 1, 1,  	-1.0f,  0.0f,  0.0f,

			// Right face					    
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    1.0f,  0.0f,  0.0f,
			0.5f, 0.5f, -0.5f,    1, 1, 1, 1,  	 1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,   1, 1, 1, 1, 	 1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,   1, 1, 1, 1, 	 1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, 0.5f,    1, 1, 1, 1,  	 1.0f,  0.0f,  0.0f,
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    1.0f,  0.0f,  0.0f,

			// Bottom face					    
			-0.5f, -0.5f, -0.5f,  1, 1, 1, 1,	 0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,   1, 1, 1, 1, 	 0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, 0.5f,    1, 1, 1, 1,  	 0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, 0.5f,    1, 1, 1, 1,  	 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, 0.5f,   1, 1, 1, 1, 	 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  1, 1, 1, 1,	 0.0f, -1.0f,  0.0f,

			// Top face						    
			-0.5f, 0.5f, -0.5f,   1, 1, 1, 1,    0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, -0.5f,    1, 1, 1, 1,    0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, 0.5f,     1, 1, 1, 1,    0.0f,  1.0f,  0.0f,
			-0.5f, 0.5f, 0.5f,    1, 1, 1, 1,    0.0f,  1.0f,  0.0f,
			-0.5f, 0.5f, -0.5f,   1, 1, 1, 1,    0.0f,  1.0f,  0.0f
	};
}

float* Mesh::GetVertices(Vector2 minCoords, Vector2 maxCoords)
{
	return new float[432]
	{
		-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y, 0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y, 0.0f,  0.0f, -1.0f,
			0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y, 0.0f,  0.0f, -1.0f,
			0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y, 0.0f,  0.0f, -1.0f,
			-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y, 0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y, 0.0f,  0.0f, -1.0f,

			// Front face												     
			-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y, 0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y, 0.0f,  0.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,	0.0f,  0.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,	0.0f,  0.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y, 0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y, 0.0f,  0.0f, 1.0f,

			// Left face												    
			-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	-1.0f,  0.0f,  0.0f,
			-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	-1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,	-1.0f,  0.0f,  0.0f,
			-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	-1.0f,  0.0f,  0.0f,

			// Right face												     
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,		1.0f,  0.0f,  0.0f,
			0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,	1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,	1.0f,  0.0f,  0.0f,
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,		1.0f,  0.0f,  0.0f,

			// Bottom face												     
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,	0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,	0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,	0.0f, -1.0f,  0.0f,

			// Top face													     
			-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y, 0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, -0.5f, 1, 1, 1, 1, maxCoords.x, maxCoords.y,  0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	  0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, 0.5f, 1, 1, 1, 1, maxCoords.x, minCoords.y,	  0.0f,  1.0f,  0.0f,
			-0.5f, 0.5f, 0.5f, 1, 1, 1, 1, minCoords.x, minCoords.y,  0.0f,  1.0f,  0.0f,
			-0.5f, 0.5f, -0.5f, 1, 1, 1, 1, minCoords.x, maxCoords.y,  0.0f,  1.0f,  0.0f
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