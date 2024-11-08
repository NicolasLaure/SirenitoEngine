#include "Entity/Entity2D/Entity2D.h"
#include "Collisions/CollisionManager.h"

void Entity2D::Update()
{
}

void Entity2D::Draw()
{
}

void Entity2D::HandleCollision(Entity2D other)
{
	if (CollisionManager::CheckCollision(*this, other))
	{
		isColliding = true;
		if (!collider.isTrigger)
		{
			SetPosition(prevpos);
		}
	}
	else
		isColliding = false;
}

bool Entity2D::IsColliding()
{
	return isColliding;
}

Vector3 Entity2D::GetPrevPos()
{
	return prevpos;
}

void Entity2D::SetPrevPos(Vector3 newPrev)
{
	prevpos = newPrev;
}
