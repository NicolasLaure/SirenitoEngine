#include "Knuckles.h"

Knuckles::Knuckles(float size, Vector3 initialPosition, Renderer* rendererInstance)
{
	knuckles = new Sprite("res/textures/Knuckles_Sprite_Sheet.png", initialPosition, Vector3(), size, size, rendererInstance);
	knuckles->collider = { size,size, false };
	SetNewState(KnucklesStates::Idle);
}

void Knuckles::Update(Input* inputInstance)
{
	Vector3 dir = Vector3();
	float xAxis = 0;
	float yAxis = 0;
	float zAxis = 0;
	if (inputInstance->isKeyPressed(Keys::A))
	{
		float prevX = xAxis;
		xAxis = -1.0f;
		if (currentState != KnucklesStates::Run && (currentState != KnucklesStates::Push))
			SetNewState(KnucklesStates::Run);
	}
	if (inputInstance->isKeyPressed(Keys::D))
	{
		float prevX = xAxis;
		xAxis = 1.0f;
		if (currentState != KnucklesStates::Run && (currentState != KnucklesStates::Push))
			SetNewState(KnucklesStates::Run);
	}

	if (inputInstance->isKeyPressed(Keys::W))
	{
		float prevZ = zAxis;
		zAxis = 1.0f;
		if (currentState != KnucklesStates::Run && (currentState != KnucklesStates::Push))
			SetNewState(KnucklesStates::Run);
	}
	if (inputInstance->isKeyPressed(Keys::S))
	{
		float prevZ = zAxis;
		zAxis = -1.0f;
		if (currentState != KnucklesStates::Run && (currentState != KnucklesStates::Push))
			SetNewState(KnucklesStates::Run);
	}

	if (xAxis != 0)
		knuckles->SetScale(Vector3(xAxis, 1, 1));
	else if (currentState != KnucklesStates::Idle && currentState != KnucklesStates::Spin)
		SetNewState(KnucklesStates::Idle);

	if (inputInstance->isKeyDown(Keys::SPACE))
	{
		if (currentState != KnucklesStates::Spin)
			SetNewState(KnucklesStates::Spin);
		else
			SetNewState(KnucklesStates::Idle);
	}

	dir = Vector3(xAxis, yAxis, zAxis);

	knuckles->Translate(dir * knucklesSpeed);
}

void Knuckles::Draw()
{
	knuckles->Draw();
}

void Knuckles::OnCollision()
{
	if (currentState != KnucklesStates::Push)
		SetNewState(KnucklesStates::Push);
}

void Knuckles::SetNewState(KnucklesStates state)
{
	currentState = state;

	switch (currentState)
	{
	case KnucklesStates::Idle:
		knuckles->SetAnimation("res/textures/Knuckles_Sprite_Sheet.png", { 0,0 }, 36, 39);
		break;
	case KnucklesStates::Run:
		knuckles->SetAnimation("res/textures/Knuckles_Sprite_Sheet.png", { 339,48 }, 40, 38, 4, 1, true);
		knuckles->animation->Play();
		break;
	case KnucklesStates::Spin:
		knuckles->SetAnimation("res/textures/Knuckles_Sprite_Sheet.png", { 1,130 }, 32, 32, 6, 1, true);
		knuckles->animation->Play();
		break;
	case KnucklesStates::Push:
		knuckles->SetAnimation("res/textures/Knuckles_Sprite_Sheet.png", { 426,96 }, 35, 35, 4, 1, true);
		knuckles->animation->Play();
		break;
	}
}

Sprite* Knuckles::GetEntity()
{
	return knuckles;
}

void Knuckles::CheckCollision(Entity2D other)
{
	Vector3 triedPosition = knuckles->GetPosition();
	knuckles->HandleCollision(other);
	knuckles->SetPrevPos(knuckles->GetPosition());

	Vector3 actualPosition = knuckles->GetPosition();
	if ((triedPosition.x != actualPosition.x ||
		triedPosition.y != actualPosition.y) && currentState != KnucklesStates::Push)
	{
		SetNewState(KnucklesStates::Push);
	}

}

