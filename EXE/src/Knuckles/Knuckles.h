#pragma once
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "Entity/Entity2D/Shape/Shapes/Rectangle.h"
#include "Input/Input.h"

enum class KnucklesStates
{
	Idle,
	Walk,
	Run,
	Spin,
	Push
};

class Knuckles
{
private:
	Sprite* knuckles;
	float knucklesSpeed = 10.0f;

	KnucklesStates currentState;

public:
	Knuckles(float size, Vector3 initialPosition, Renderer* rendererInstance);

	void Update(Input* inputInstance);
	void Draw();

	void OnCollision();
	void SetNewState(KnucklesStates state);

	Sprite* GetEntity();

	void CheckCollision(Entity2D other);
};