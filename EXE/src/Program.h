#pragma once
#include "DLL/BaseGame/BaseGame.h"
#include "DLL/Entity/Entity2D/Sprite/Sprite.h"

SIRENITO_API class Program : public BaseGame
{
private:
	Sprite* sprite;
	Sprite* sans;
public:
	Program(int width, int height, const char* title);
	~Program();
	void Update() override;
	void Draw() override;
};