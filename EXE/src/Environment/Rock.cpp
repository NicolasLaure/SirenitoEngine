#include "Rock.h"

Rock::Rock(float size, Vector3 initialPosition, Renderer* rendererInstance)
{
	rockSprite = new Sprite("res/textures/Rock.jfif", initialPosition, Vector3(), size, size, rendererInstance);
	rockSprite->collider = { size, size, false };
	rockSprite->SetAnimation("res/textures/Rock.jfif", { 74,20 }, 85, 57);
}

void Rock::OnCollision()
{
}

void Rock::Update()
{
}

void Rock::Draw()
{
	rockSprite->Draw();
}

Sprite* Rock::GetEntity()
{
	return rockSprite;
}
