#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Textures/Importer/TextureImporter.h"


Sprite::Sprite(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Material material, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, material, rendererInstance);
}

Sprite::Sprite(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, position, eulers, width, height, Material(), rendererInstance);
}

Sprite::Sprite(const char* texturePath, float width, float height, Material material, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), width, height, material, rendererInstance);
}

Sprite::Sprite(const char* texturePath, float width, float height, Renderer* rendererInstance)
{
	Init(texturePath, Vector3(), Vector3(), width, height, Color::white(), rendererInstance);
}

void Sprite::Init(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Material material, Renderer* rendererInstance)
{
	this->texture = TextureImporter::ImportTexture(texturePath);
	this->width = width;
	this->height = height;
	this->collider.width = width;
	this->collider.height = height;

	this->rendererInstance = rendererInstance;
	this->material = material;
	VAO = rendererInstance->CreateVertexArray();
	VBO = rendererInstance->CreateBuffer();
	EBO = rendererInstance->CreateBuffer();

	transform = new Transform();
	transform->SetPositionAndRotation(position, Quaternion::Euler(eulers));

	rendererInstance->SetData(transform, material, true, GetTransformedVertices(width, height), 36, GetIndices(), 6, VAO, VBO, EBO);
}

Sprite::~Sprite()
{
	delete transform;

	if (animation != nullptr)
		delete animation;
}

void Sprite::SetTexture(const char* path)
{
	texture = TextureImporter::ImportTexture(path);
}

void Sprite::SetAnimation(const char* path, Vector2 initialCoords, int frameWidth, int frameHeight, int framesQuantity, float animationDuration, bool canLoop)
{
	texture = TextureImporter::ImportTexture(path);
	if (animation != nullptr)
		delete animation;

	animation = new Animation(texture, initialCoords, frameWidth, frameHeight, framesQuantity, animationDuration, canLoop);
}
void Sprite::SetAnimation(const char* path, Vector2 initialCoords, int frameWidth, int frameHeight)
{
	texture = TextureImporter::ImportTexture(path);
	if (animation != nullptr)
		delete animation;

	animation = new Animation(texture, initialCoords, frameWidth, frameHeight);
}

void Sprite::Draw()
{
	if (animation != nullptr)
	{
		animation->UpdateAnimation();
		rendererInstance->SetData(transform, material, true, GetTransformedVertices(width, height, animation->currentFrame.GetMin(), animation->currentFrame.GetMax()), 48, GetIndices(), 6, VAO, VBO, EBO);
	}
	else
		rendererInstance->SetData(transform, material, true, GetTransformedVertices(width, height), 48, GetIndices(), 6, VAO, VBO, EBO);

	rendererInstance->Draw(VAO, 6, texture.GetId());
}

float* Sprite::GetTransformedVertices(float width, float height)
{
	return GetTransformedVertices(width, height, Vector2(0, 0), Vector2(1, 1));
}

float* Sprite::GetTransformedVertices(float width, float height, Vector2 minCoords, Vector2 maxCoords)
{
	return new float[48]
	{
		//Top Right
		width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, maxCoords.x, maxCoords.y, 0.0f,  0.0f,  1.0f,
		//Bottom Right
		width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, maxCoords.x, minCoords.y, 0.0f,  0.0f,  1.0f,
		//Bottom Left
		-width / 2, -height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, minCoords.x, minCoords.y, 0.0f,  0.0f,  1.0f,
		//Top Left
		-width / 2, height / 2, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, minCoords.x, maxCoords.y, 0.0f,  0.0f,  1.0f
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