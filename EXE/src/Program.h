#pragma once
#include "BaseGame/BaseGame.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Entity/Entity2D/Shape/Shapes/Rectangle.h"
#include <vector>

SIRENITO_API class Program : public BaseGame
{
private:
	Sprite* eirika;
	Sprite* hector;

	bool eirikaAlive = true;
	bool hectorAlive = true;

	int eirikaBlinkMax = 40;
	int eirikaBlinkCount = 0;

	int hectorBlinkMax = 5;
	int hectorBlinkCount = 0;

public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};