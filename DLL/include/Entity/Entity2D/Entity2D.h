#pragma once
#include "Entity/Entity.h"

#include "Renderer/Renderer.h"
#include "Utilities/Exporter.h"
#include "Collisions/Collider.h"

SIRENITO_API class Entity2D : public entity
{
protected:
	Renderer* rendererInstance;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	Vector3 prevpos = Vector3();
	bool isColliding= false;

	SIRENITO_API Vector3 GetPrevPos();
public:
	Collider collider;

	SIRENITO_API virtual void Update() override;
	SIRENITO_API virtual void Draw() override;

	SIRENITO_API void HandleCollision(Entity2D other);
	SIRENITO_API void SetPrevPos(Vector3 newPrev);
	SIRENITO_API bool IsColliding();
};