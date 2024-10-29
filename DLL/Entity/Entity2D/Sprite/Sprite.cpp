#include "Sprite.h"
#include "Textures/Importer/TextureImporter.h"


Sprite::Sprite(const char* texturePath, glm::vec3 position, glm::vec3 eulers, float width, float height, Color color, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, color, rendererInstance);
}

Sprite::Sprite(const char* texturePath, glm::vec3 position, glm::vec3 eulers, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, Color::white(), rendererInstance);
}

Sprite::Sprite(const char* texturePath, float width, float height, Color color, Renderer* rendererInstance)
{
	Init(texturePath, glm::vec3(0), glm::vec3(0), width, height, color, rendererInstance);
}

Sprite::Sprite(const char* texturePath, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, glm::vec3(0), glm::vec3(0), width, height, Color::white(), rendererInstance);
}

void Sprite::Init(const char* texturePath, glm::vec3 position, glm::vec3 eulers, float width, float height, Color color, Renderer* rendererInstance)
{
	this->texture = TextureImporter::ImportTexture(texturePath);
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

	rendererInstance->SetData(trs, color, true, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
}

Sprite::~Sprite()
{
	if (animation != nullptr)
		delete animation;
}

void Sprite::SetTexture(const char* path)
{
	texture = TextureImporter::ImportTexture(path);
}

void Sprite::SetAnimation(const char* path, Vector2f initialCoords, int frameWidth, int frameHeight, int framesQuantity, bool canLoop)
{
	texture = TextureImporter::ImportTexture(path);
	if (animation != nullptr)
		delete animation;

	animation = new Animation(&texture, initialCoords, frameWidth, frameHeight, framesQuantity, canLoop);
}

void Sprite::Draw()
{
	if (animation != nullptr)
		rendererInstance->SetData(trs, color, true, GetVertices(width, height, animation->currentFrame.GetMin(), animation->currentFrame.GetMax()), 36, GetIndices(), 6, VAO, VBO, EBO);
	else
		rendererInstance->SetData(trs, color, true, GetVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);

	rendererInstance->Draw(VAO, 6, texture.GetId());
}

float* Sprite::GetVertices(float width, float height)
{
	return new float[36]
		{
			width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //Bottom Right
				width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //Top Right
				-width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //Top Left
				-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  //Bottom Left
		};
}

float* Sprite::GetVertices(float width, float height, Vector2f minCoords, Vector2f maxCoords)
{
	return new float[36]
		{
			width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, maxCoords.x, maxCoords.y, //Bottom Right
				width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, maxCoords.x, minCoords.y, //Top Right
				-width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, minCoords.x, minCoords.y, //Top Left
				-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, minCoords.x, maxCoords.y  //Bottom Left
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