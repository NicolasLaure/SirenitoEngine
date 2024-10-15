#include "Sprite.h"
#include "Textures/Importer/TextureImporter.h"


Sprite::Sprite(glm::vec3 position, glm::vec3 eulers, float width, float height, Color color, Renderer* rendererInstance)
{
	this->width = width;
	this->height = height;

	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	SetPosition(position);
	SetRotation(eulers);
	SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	rendererInstance->SetData(trs, color, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
}

Sprite::Sprite(float width, float height, Color color, Renderer* rendererInstance)
{
	this->width = width;
	this->height = height;

	this->rendererInstance = rendererInstance;
	this->color = color;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	rendererInstance->SetData(trs, color, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
}

Sprite::~Sprite()
{
}

void Sprite::SetTexture(const char* path)
{
	texture = TextureImporter::ImportTexture(path);
}

void Sprite::Draw()
{
	rendererInstance->SetData(trs, color, texture, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
	rendererInstance->Draw(VAO, 6, texture);
}

float* Sprite::GetVertices(float width, float height)
{
	return new float[36]
		{
			width / 2, -height / 2, 0.0f,           1.0f, 1.0f, 1.0f, 1.0f,        1.0f, 1.0f,
			width / 2, height / 2, 0.0f,           1.0f, 1.0f, 1.0f, 1.0f,         1.0f, 0.0f,
			-width / 2, height / 2, 0.0f,          1.0f, 1.0f, 1.0f, 1.0f,         0.0f, 0.0f,
			-width / 2, -height / 2, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,         0.0f, 1.0f
		};
}

unsigned int* Sprite::GetIndices()
{
	return new unsigned int[6]
		{
			0, 1, 3,
				1, 2, 3
		};
}
