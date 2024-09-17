#include "Entity.h"

void Entity::SetTRS(glm::vec3 pos, glm::quat rot, glm::vec3 scale)
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 rotationMatrix = glm::mat4_cast(rot);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	trs = translateMatrix * rotationMatrix * scaleMatrix;
}

void Entity::Update()
{
}

void Entity::Draw()
{
}

glm::vec3 Entity::GetPosition()
{
	return pos;
}

glm::quat Entity::GetRotation()
{
	return rotation;
}

glm::vec3 Entity::GetEulerAngles()
{
	return glm::eulerAngles(rotation);
}

glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::SetPosition(glm::vec3 newPos)
{
	pos = newPos;
	SetTRS(pos, rotation, scale);
}

void Entity::SetRotation(glm::vec3 eulers)
{
	//if fails, apply radians to each axis
	SetRotation(glm::quat(eulers));
}

void Entity::SetRotation(glm::quat rotation)
{
	this->rotation = rotation;
	SetTRS(pos, this->rotation, scale);
}

void Entity::SetRotation(float angle, glm::vec3 axis)
{
	rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
	SetTRS(pos, rotation, scale);
}

void Entity::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	SetTRS(pos, rotation, scale);
}

void Entity::Translate(glm::vec3 translation)
{
	SetPosition(pos + translation);
}

void Entity::Rotate(glm::quat rotation)
{
	SetRotation(this->rotation * rotation);
}

void Entity::Rotate(glm::vec3 eulers)
{
	Rotate(glm::quat(eulers));
}


void Entity::Scale(glm::vec3 scalation)
{
	SetScale(scale + scalation);
}
