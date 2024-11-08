#include "Entity/Entity.h"

void entity::SetTRS(glm::vec3 pos, glm::quat rot, glm::vec3 scale)
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 rotationMatrix = glm::mat4_cast(rot);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	trs = translateMatrix * rotationMatrix * scaleMatrix;
}

void entity::Update()
{
}

void entity::Draw()
{
}

Vector3 entity::GetPosition()
{
	return Vector3::FromGlm(pos);
}

glm::quat entity::GetRotation()
{
	return rotation;
}

Vector3 entity::GetEulerAngles()
{
	return Vector3::FromGlm(glm::eulerAngles(rotation));
}

Vector3 entity::GetScale()
{
	return Vector3::FromGlm(scale);
}

void entity::SetPosition(Vector3 newPos)
{
	pos = newPos.ToGlm();
	SetTRS(pos, rotation, scale);
}

void entity::SetRotation(Vector3 eulers)
{
	//if fails, apply radians to each axis
	SetRotation(glm::quat(eulers.ToGlm()));
}

void entity::SetRotation(glm::quat rotation)
{
	this->rotation = rotation;
	SetTRS(pos, this->rotation, scale);
}

void entity::SetRotation(float angle, Vector3 axis)
{
	rotation = glm::rotate(glm::mat4(1.0f), angle, axis.ToGlm());
	SetTRS(pos, rotation, scale);
}

void entity::SetScale(Vector3 newScale)
{
	scale = newScale.ToGlm();
	SetTRS(pos, rotation, scale);
}

void entity::Translate(Vector3 translation)
{
	SetPosition(Vector3::FromGlm(pos) + translation);
}

void entity::Rotate(glm::quat rotation)
{
	SetRotation(this->rotation * rotation);
}

void entity::Rotate(Vector3 eulers)
{
	Rotate(glm::quat(eulers.ToGlm()));
}


void entity::Scale(Vector3 scalation)
{
	SetScale(Vector3::FromGlm(scale) + scalation);
}
