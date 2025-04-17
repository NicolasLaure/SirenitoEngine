#include "Entity/Entity.h"

void entity::SetTRS(Vector3 pos, Quaternion rot, Vector3 scale)
{
	MY4X4 translateMatrix = MY4X4::Translate(pos);
	MY4X4 rotationMatrix = MY4X4::Rotate(rot);
	MY4X4 scaleMatrix = MY4X4::Scale(scale);

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
	return pos;
}

Quaternion entity::GetRotation()
{
	return rotation;
}

Vector3 entity::GetEulerAngles()
{
	return rotation.eulerAngles();
}

Vector3 entity::GetScale()
{
	return scale;
}

void entity::SetPosition(Vector3 newPos)
{
	pos = newPos;
	SetTRS(pos, rotation, scale);
}

void entity::SetRotation(Vector3 eulers)
{
	//if fails, apply radians to each axis
	SetRotation(Quaternion::Euler(eulers.x, eulers.y, eulers.z));
}

void entity::SetRotation(Quaternion rotation)
{
	this->rotation = rotation;
	SetTRS(pos, this->rotation, scale);
}

void entity::SetRotation(float angle, Vector3 axis)
{
	SetTRS(pos, Quaternion::AngleAxis(angle, axis), scale);
}

void entity::SetScale(Vector3 newScale)
{
	scale = newScale.ToGlm();
	SetTRS(pos, rotation, scale);
}

void entity::Translate(Vector3 translation)
{
	SetPosition(pos + translation);
}

void entity::Rotate(Quaternion rotation)
{
	SetRotation(this->rotation * rotation);
}

void entity::Rotate(Vector3 eulers)
{
	Rotate(Quaternion::Euler(eulers.x, eulers.y, eulers.z));
}


void entity::Scale(Vector3 scalation)
{
	SetScale(scale + scalation);
}
