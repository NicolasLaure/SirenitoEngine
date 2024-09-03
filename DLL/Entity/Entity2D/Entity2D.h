#pragma once
#include "Entity/Entity.h"

#include "Renderer/Renderer.h"
#include "Utilities/Exporter.h"

SIRENITO_API class Entity2D : public Entity
{
protected:
	Renderer* rendererInstance;
public:
	SIRENITO_API virtual void Update();
	SIRENITO_API virtual void Draw();
};