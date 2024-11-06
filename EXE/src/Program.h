#pragma once
#include "BaseGame/BaseGame.h"
#include "Entity/Entity2D/Sprite/Sprite.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Sprite* background;
	Sprite* heart;
	Sprite* explosion;
	Sprite* sonic;

	float sansScaleRatio = 0.1f;
	float heartSpeed = 5.0f;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};