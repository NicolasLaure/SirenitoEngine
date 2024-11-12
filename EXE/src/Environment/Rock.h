#pragma once
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Entity/Entity2D/Shape/Shapes/Rectangle.h"

class Rock
{
private:
	Sprite* rockSprite;

public:
	Rock(float size, Vector3 initialPosition, Renderer* rendererInstance);
	void OnCollision();

	void Update();
	void Draw();

	Sprite* GetEntity();
};