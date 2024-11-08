#include "Collisions/CollisionManager.h"

bool CollisionManager::CheckCollision(Entity2D entity, Entity2D other)
{
	return entity.GetPosition().x + entity.collider.width / 2 >= other.GetPosition().x - other.collider.width / 2 &&
		entity.GetPosition().x - entity.collider.width / 2 <= other.GetPosition().x + other.collider.width / 2 &&
		entity.GetPosition().y + entity.collider.height / 2 >= other.GetPosition().y - other.collider.height / 2 &&
		entity.GetPosition().y - entity.collider.height / 2 <= other.GetPosition().y + other.collider.height / 2;
}