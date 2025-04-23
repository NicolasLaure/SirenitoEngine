#include "Collisions/CollisionManager.h"

bool CollisionManager::CheckCollision(Entity2D Entity, Entity2D other)
{
	return Entity.transform.GetPosition().x + Entity.collider.width / 2 >= other.transform.GetPosition().x - other.collider.width / 2 &&
		Entity.transform.GetPosition().x - Entity.collider.width / 2 <= other.transform.GetPosition().x + other.collider.width / 2 &&
		Entity.transform.GetPosition().y + Entity.collider.height / 2 >= other.transform.GetPosition().y - other.collider.height / 2 &&
		Entity.transform.GetPosition().y - Entity.collider.height / 2 <= other.transform.GetPosition().y + other.collider.height / 2;
}