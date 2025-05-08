#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity.h"
#include "Renderer/Renderer.h"


SIRENITO_API class Entity3D : public Entity
{
protected:
	Renderer* rendererInstance;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

public:

	SIRENITO_API virtual void Update() override;
	SIRENITO_API virtual void Draw() override;

};