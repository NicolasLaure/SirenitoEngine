#pragma once
#include "Entity/Entity2D/Entity2D.h"
#include "glm.hpp"
#include "Utilities/Vector2.h"
#include "Utilities/Vector3.h"
#include "Utilities/Exporter.h"
#include "Animation/Animation.h"
#include "Textures/Texture.h"
#include "Utilities/Material.h"

SIRENITO_API class Sprite : public Entity2D
{
protected:
	float width;
	float height;
	Texture texture;
	Material material;


	SIRENITO_API void Init(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Material material, Renderer* rendererInstance);
	SIRENITO_API float* GetTransformedVertices(float width, float height);
	SIRENITO_API float* GetTransformedVertices(float width, float height, Vector2 minCoords, Vector2 maxCoords);
	SIRENITO_API unsigned int* GetIndices();
	SIRENITO_API void SetUVCoords(Vector2 minCoords, Vector2 maxCoords);
public:
	Animation* animation = nullptr;

	SIRENITO_API Sprite(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Material material, Renderer* rendererInstance);
	SIRENITO_API Sprite(const char* texturePath, Vector3 position, Vector3 eulers, float width, float height, Renderer* rendererInstance);
	SIRENITO_API Sprite(const char* texturePath, float width, float height, Material material, Renderer* rendererInstance);
	SIRENITO_API Sprite(const char* texturePath, float width, float height, Renderer* rendererInstance);
	SIRENITO_API ~Sprite();

	SIRENITO_API void SetTexture(const char* path);
	SIRENITO_API void SetAnimation(const char* path, Vector2 initialCoords, int frameWidth, int frameHeight, int framesQuantity, float animationDuration, bool canLoop);
	SIRENITO_API void SetAnimation(const char* path, Vector2 initialCoords, int frameWidth, int frameHeight);
	SIRENITO_API void Draw() override;
};