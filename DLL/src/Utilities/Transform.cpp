#include "Utilities/Transform.h"
#include <iostream>

#pragma region Constructors

Transform::Transform()
{
	localPosition = Vector3::Zero();
	localRotation = Quaternion::identity();
	scale = Vector3::One();

	_worldPosition = localPosition;
	_worldRotation = localRotation;
	_localScale = scale;
	_lossyScale = scale;

	matrixTRS = MY4X4::TRS(localPosition, localRotation, scale);
	_name = "";

	_children = new List<Transform*>();
	parent = nullptr;
}

Transform::Transform(string name)
{
	localPosition = Vector3::Zero();
	localRotation = Quaternion::identity();
	scale = Vector3::One();

	_worldPosition = localPosition;
	_worldRotation = localRotation;
	_localScale = scale;
	_lossyScale = scale;

	matrixTRS = MY4X4::TRS(localPosition, localRotation, scale);
	_name = name;

	_children = new List<Transform*>();
	parent = nullptr;
}

Transform::Transform(string name, Vector3 pos, Quaternion q, Vector3 s)
{
	localPosition = pos;
	localRotation = q;
	scale = s;

	_worldPosition = localPosition;
	_worldRotation = localRotation;
	_localScale = scale;
	_lossyScale = scale;

	matrixTRS = MY4X4::TRS(localPosition, localRotation, scale);

	_name = name;

	_children = new List<Transform*>();
	parent = nullptr;
}

Transform::~Transform()
{
	int childrenCount = _children->GetCount();
	if (childrenCount > 0)
	{
		for (int i = 0; i < childrenCount; i++)
			delete _children->GetValueAt(i);
	}

	delete _children;
}

#pragma endregion

#pragma region Properties

MY4X4 Transform::WorldToLocalMatrix()
{
	if (parent == nullptr)
		return matrixTRS;

	return matrixTRS.GetInverse() * parent->WorldToLocalMatrix();
}

MY4X4 Transform::LocalToWorldMatrix()
{
	if (parent == nullptr)
		return matrixTRS;

	return parent->LocalToWorldMatrix() * matrixTRS;
}

Vector3 Transform::GetPosition()
{
	return LocalToWorldMatrix().GetPosition();
}

void Transform::SetPosition(Vector3 value)
{
	SetLocalPosition(InverseTransformPoint(value));
}

Vector3 Transform::GetLocalPosition()
{
	return localPosition;
}
void Transform::SetLocalPosition(Vector3 value)
{
	localPosition = value;
	matrixTRS.SetTRS(localPosition, localRotation, _localScale);
}

Vector3 Transform::GetEulerAngles()
{
	return GetRotation().eulerAngles();
}
void Transform::SetEulerAngles(Vector3 value)
{
	SetPositionAndRotation(localPosition, Quaternion::Euler(value.x, value.y, value.z));
}

Vector3 Transform::GetLocalEulerAngles()
{
	return matrixTRS.GetRotation().eulerAngles();
}
void Transform::SetLocalEulerAngles(Vector3 value) { SetLocalPositionAndRotation(localPosition, Quaternion::Euler(value.x, value.y, value.z)); }

Vector3 Transform::GetRight()
{
	return LocalToWorldMatrix().MultiplyVector(Vector3::Right());
}
void Transform::SetRight(Vector3 value)
{
	SetRotation(Quaternion::FromToRotation(Vector3::Right(), value));

	if (value == Vector3::Left())
	{
		SetRotation(GetRotation() * Quaternion::Euler(0, 180, 0));
	}
}

Vector3 Transform::GetUp()
{
	return LocalToWorldMatrix().MultiplyVector(Vector3::Up());
}
void Transform::SetUp(Vector3 value)
{
	SetRotation(Quaternion::FromToRotation(Vector3::Up(), value));

	if (value == Vector3::Down())
	{
		SetRotation(GetRotation() * Quaternion::Euler(180, 0, 0));
	}
}

Vector3 Transform::GetForward()
{
	return LocalToWorldMatrix().MultiplyVector(Vector3::Forward());
}
void Transform::SetForward(Vector3 value)
{
	SetRotation(Quaternion::LookRotation(value));
}


Quaternion Transform::GetRotation()
{
	return LocalToWorldMatrix().GetRotation();
}
void Transform::SetRotation(Quaternion value)
{
	//Should set local rotation in a certain way that the global rotation matches when multiplying with all parents
	Transform worldTransform = Transform("World", Vector3::Zero(), value, Vector3::One());
	worldTransform.parent = parent;
	Quaternion newRotation = worldTransform.WorldToLocalMatrix().GetInverse().GetRotation();

	SetLocalRotation(newRotation);
}

Quaternion Transform::GetLocalRotation()
{
	return localRotation;
}
void Transform::SetLocalRotation(Quaternion value)
{
	localRotation = value;
	rotationEulers = Vector3(localRotation.eulerAngles());
	matrixTRS.SetTRS(localPosition, localRotation, GetLocalScale());
}

Vector3 Transform::GetLocalScale()
{
	return Vector3(matrixTRS.GetlossyScale());
}
void Transform::SetLocalScale(Vector3 value)
{
	scale = value;
	_localScale = value;
	matrixTRS.SetTRS(localPosition, localRotation, scale);
}

Vector3 Transform::GetlossyScale()
{
	return LocalToWorldMatrix().GetlossyScale();
}

Transform* Transform::GetParent()
{
	return parent;
}

Transform* Transform::Root()
{
	if (parent == nullptr)
		return this;

	return parent->Root();
}

int Transform::ChildCount()
{
	return _children->GetCount();
}

string Transform::GetName()
{
	return _name;
}

void Transform::SetTRS(MY4X4 trs)
{
	matrixTRS = trs;
	localPosition = matrixTRS.GetPosition();
	localRotation = matrixTRS.GetRotation();
}

#pragma endregion

#pragma region Functions

/*	void TestUpdate()
{
	localRotation = Quaternion.Euler(rotationEulers);

	matrixTRS.SetTRS(localPosition, localRotation, scale);
	_worldPosition = LocalToWorldMatrix.GetPosition();
	_worldRotation = Rotation;
	_localScale = LocalScale;
	_lossyScale = lossyScale;

	root = Root;

	foreach(MyTransform child in _children)
	{
		child.TestUpdate();
	}
}*/

#pragma region Hierarchy

void Transform::SetParent(Transform* newParent)
{
	parent = newParent;
	matrixTRS.SetTRS(localPosition, localRotation, scale);
	_worldPosition = GetPosition();
	_worldRotation = GetRotation();
}

void Transform::SetParent(Transform* newParent, bool worldPositionStays)
{
	if (parent != nullptr || newParent == nullptr)
		parent->RemoveChild(this);

	parent = newParent;
	parent->AddChild(this);

	//Update local position without moving world position
}

void Transform::RemoveChild(Transform* child)
{
	_children->Remove(child);
}

void Transform::AddChild(Transform* child)
{
	_children->PushBack(child);
}

void Transform::AddChild(Transform* child, int position)
{
	if (_children->Contains(child))
		_children->Remove(child);

	_children->Insert(child, position);
}

void Transform::DetachChildren()
{
	while (_children->GetCount() > 0)
	{
		_children->GetValueAt(0)->GetParent()->RemoveChild(_children->GetValueAt(0));
		_children->GetValueAt(0)->SetParent(nullptr);
	}
}

void Transform::SetAsFirstSibling()
{
	parent->RemoveChild(this);
	parent->AddChild(this, 0);
}

void Transform::SetAsLastSibling()
{
	parent->RemoveChild(this);
	parent->AddChild(this, parent->ChildCount());
}

void Transform::SetSiblingIndex(int index)
{
	parent->RemoveChild(this);
	parent->AddChild(this, index);
}

int Transform::GetSiblingIndex()
{
	if (parent != nullptr)
		return parent->GetChildIndex(this);
}

Transform* Transform::Find(const char* n)
{
	for (int i = 0; i < _children->GetCount(); i++)
	{
		if (_children->GetValueAt(i)->_name == n)
			return _children->GetValueAt(i);

		if (_children->GetValueAt(i)->ChildCount() > 0)
		{
			Transform* child = _children->GetValueAt(i)->Find(n);
			if (child != nullptr)
				return child;
		}
	}
	return nullptr;
}

int Transform::GetChildIndex(Transform* child)
{
	for (int i = 0; i < _children->GetCount(); i++)
	{
		if (_children->GetValueAt(i) == child)
			return i;
	}
	return -1;
}

#pragma endregion

void Transform::SetPositionAndRotation(Vector3 position, Quaternion GetRotation)
{
	SetPosition(position);
	SetRotation(GetRotation);
}

void Transform::SetLocalPositionAndRotation(Vector3 newLocalPosition, Quaternion newLocalRotation)
{
	SetLocalPosition(newLocalPosition);
	SetLocalRotation(newLocalRotation);
}

void Transform::GetPositionAndRotation(Vector3* position, Quaternion* GetRotation)
{
	MY4X4 transformedMatrix = LocalToWorldMatrix();
	*position = transformedMatrix.GetPosition();
	*GetRotation = transformedMatrix.GetRotation();
}

void Transform::GetLocalPositionAndRotation(Vector3* localPosition, Quaternion* localRotation)
{
	*localPosition = matrixTRS.GetPosition();
	*localRotation = matrixTRS.GetRotation();
}

#pragma region Translates

void Transform::Translate(Vector3 translation, Space relativeTo)
{
	if (relativeTo == Space::Self)
	{
		Translate(translation);
		return;
	}

	localPosition = InverseTransformPoint(GetPosition() + translation);
}

void Transform::Translate(Vector3 translation)
{
	SetLocalPosition(GetLocalPosition() + translation);
}

void Transform::Translate(float x, float y, float z, Space relativeTo)
{
	Translate(Vector3(x, y, z), relativeTo);
}

void Transform::Translate(float x, float y, float z)
{
	Translate(Vector3(x, y, z));
}

void Transform::Translate(Vector3 translation, Transform relativeTo)
{
	MY4X4 auxSelfWorldMatrix = LocalToWorldMatrix();
	MY4X4 auxRelativeWorldMatrix = relativeTo.LocalToWorldMatrix();
	auxRelativeWorldMatrix.SetColumn(3, Vector4(0, 0, 0, 1));

	Vector4 result = auxRelativeWorldMatrix * Vector4(translation.x, translation.y, translation.z, 1);

	SetPosition(auxSelfWorldMatrix.GetPosition() + Vector3(result.x, result.y, result.z));
}

void Transform::Translate(float x, float y, float z, Transform relativeTo)
{
	Translate(Vector3(x, y, z), relativeTo);
}

#pragma endregion

#pragma region Rotates

void Transform::Rotate(Vector3 eulers, Space relativeTo)
{
	if (relativeTo == Space::Self)
	{
		SetLocalRotation(GetLocalRotation() * Quaternion::Euler(eulers.x, eulers.y, eulers.z));
		return;
	}

	Rotate(eulers);
}

void Transform::Rotate(Vector3 eulers)
{
	SetRotation(GetRotation() * Quaternion::Euler(eulers.x, eulers.y, eulers.z));
}

void Transform::Rotate(float xAngle, float yAngle, float zAngle, Space relativeTo)
{
	Rotate(Vector3(xAngle, zAngle, yAngle), relativeTo);
}

void Transform::Rotate(float xAngle, float yAngle, float zAngle)
{
	Rotate(Vector3(xAngle, zAngle, yAngle));
}

void Transform::Rotate(Vector3 axis, float angle, Space relativeTo)
{
	if (relativeTo == Space::Self)
	{
		Rotate(axis, angle);
		return;
	}
	SetRotation(GetRotation() * Quaternion::AngleAxis(angle, axis));
}

void Transform::Rotate(Vector3 axis, float angle)
{
	SetLocalRotation(GetLocalRotation() * Quaternion::AngleAxis(angle, axis));
}

#pragma endregion

void Transform::RotateAround(Vector3 point, Vector3 axis, float angle)
{
	Transform* originalParent = GetParent();
	Transform* pivotTransform = new  Transform("pivot", point, Quaternion::AngleAxis(angle, axis), Vector3::One());
	Transform* relativeTransform = new Transform("relative", Vector3::Zero(), Quaternion::identity(), Vector3::One());
	relativeTransform->SetParent(pivotTransform);
	relativeTransform->SetLocalPosition(GetPosition() - point);

	SetPosition(relativeTransform->GetPosition());
	SetRotation(relativeTransform->GetRotation());
	pivotTransform->RemoveChild(relativeTransform);

	delete pivotTransform;
	delete relativeTransform;
}

void Transform::LookAt(Transform target, Vector3 worldUp)
{
	Vector3 dir = (target.GetPosition() - GetPosition()).normalized();
	SetRotation(Quaternion::LookRotation(dir, worldUp));
}

void Transform::LookAt(Transform target)
{
	SetForward((target.GetPosition() - GetPosition()).normalized());
}

void Transform::LookAt(Vector3 worldPosition, Vector3 worldUp)
{
	SetRotation(Quaternion::LookRotation(worldPosition, worldUp));
}

void Transform::LookAt(Vector3 worldPosition)
{
	SetForward((worldPosition - GetPosition()).normalized());
}

Vector3 Transform::TransformDirection(Vector3 direction)
{
	return LocalToWorldMatrix().GetRotation() * direction;
}

Vector3 Transform::TransformDirection(float x, float y, float z)
{
	return TransformDirection(Vector3(x, y, z));
}

Vector3 Transform::InverseTransformDirection(Vector3 direction)
{
	return WorldToLocalMatrix().GetInverse().MultiplyPoint(direction);
}

Vector3 Transform::InverseTransformDirection(float x, float y, float z)
{
	return InverseTransformDirection(Vector3(x, y, z));
}

Vector3 Transform::TransformVector(Vector3 vector)
{
	return LocalToWorldMatrix().MultiplyVector(vector);
}

Vector3 Transform::TransformVector(float x, float y, float z)
{
	return TransformVector(Vector3(x, y, z));
}

Vector3 Transform::InverseTransformVector(Vector3 vector)
{
	return WorldToLocalMatrix().GetInverse().MultiplyVector(vector);
}

Vector3 Transform::InverseTransformVector(float x, float y, float z)
{
	return InverseTransformVector(Vector3(x, y, z));
}

Vector3 Transform::TransformPoint(Vector3 position)
{
	return LocalToWorldMatrix().MultiplyPoint(position);
}

Vector3 Transform::TransformPoint(float x, float y, float z)
{
	return TransformPoint(Vector3(x, y, z));
}

Vector3 Transform::InverseTransformPoint(Vector3 position)
{
	Transform worldTransform = Transform("World");
	worldTransform.parent = parent;
	return worldTransform.WorldToLocalMatrix().GetInverse().MultiplyPoint3x4(position);
}

Vector3 Transform::RelativeInverseTransformPoint(Vector3 position, Transform relativeTo)
{
	relativeTo.parent = parent;
	return relativeTo.WorldToLocalMatrix().GetInverse().MultiplyPoint3x4(position);
}

Vector3 Transform::InverseTransformPoint(float x, float y, float z)
{
	return InverseTransformPoint(Vector3(x, y, z));
}

bool Transform::IsChildOf(Transform* parent)
{
	if (this->parent == nullptr)
		return false;

	return this->parent == parent || this->parent->IsChildOf(parent);
}

#pragma endregion