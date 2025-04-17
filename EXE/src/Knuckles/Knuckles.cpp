#include "Knuckles.h"

Knuckles::Knuckles(float size, Vector3 initialPosition, Renderer* rendererInstance)
{
	knuckles = new Sprite3D("res/textures/sans-dance.jpg", initialPosition, Vector3(), size, size, rendererInstance);
	knuckles->collider = { size,size, false };
}

void Knuckles::Update(Input* inputInstance)
{
	Vector3 dir = Vector3();
	float xAxis = 0;
	float yAxis = 0;
	float zAxis = 0;


	dir = Vector3(xAxis, yAxis, zAxis);

	knuckles->Translate(dir * knucklesSpeed);
}

void Knuckles::Draw()
{
	knuckles->Draw();
}

Sprite3D* Knuckles::GetEntity()
{
	return knuckles;
}

