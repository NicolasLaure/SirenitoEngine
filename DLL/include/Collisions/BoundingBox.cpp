#include "BoundingBox.h"

BoundingBox::BoundingBox(Transform* transform, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	this->transform = transform;
	center = transform->GetPosition();
	min = Vector3::Zero();
	max = Vector3::Zero();
}

BoundingBox::BoundingBox(Transform* transform, vector<Vector3> vertices, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	this->transform = transform;
	CalculateMeshBoundingBox(vertices);
}

BoundingBox::BoundingBox(Transform* transform, vector<BoundingBox*> childrenBoxes, vector<Vector3> vertices, Renderer* rendererInstance)
{
	this->rendererInstance = rendererInstance;
	this->transform = transform;
	children = childrenBoxes;
	CalculateMeshBoundingBox(vertices);
}

void BoundingBox::AddChild(BoundingBox* child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
			return;
	}
	children.push_back(child);
}

void BoundingBox::CalculateMeshBoundingBox(vector<Vector3> vertexList)
{
	if (vertexList.size() == 0)
	{
		center = transform->GetPosition();
		min = Vector3::Zero();
		max = Vector3::Zero();
		return;
	}

	min = vertexList[0];
	max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		min = Vector3::Min(min, vertexList[i]);
		max = Vector3::Max(max, vertexList[i]);
	}

	size = max - min;
	center = (max + min) / 2;
	SetCube();
}

void BoundingBox::CalculateMeshBoundingBox(vector<Vertex> vertexList)
{
	if (vertexList.size() == 0)
	{
		center = transform->GetPosition();
		min = Vector3::Zero();
		max = Vector3::Zero();
		return;
	}

	min = vertexList[0].Position;
	max = vertexList[0].Position;

	for (int i = 1; i < vertexList.size(); i++)
	{
		min = Vector3::Min(min, vertexList[i].Position);
		max = Vector3::Max(max, vertexList[i].Position);
	}

	size = max - min;
	center = (max + min) / 2;
	SetCube();
}

void BoundingBox::CalculateCompoundBoundingBox()
{
	if (children.size() < 1)
		return;

	vector<Vector3> childrenBounds;
	vector<Vector3>parentBounds = GetBoundsVertices();
	vector<Vector3> childrenParentBounds;

	for (int i = 0; i < parentBounds.size(); i++)
		childrenParentBounds.push_back(parentBounds[i]);

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->CalculateCompoundBoundingBox();
		childrenBounds = children[i]->GetBoundsVertices();

		for (int j = 0; j < childrenBounds.size(); j++)
			childrenParentBounds.push_back(childrenBounds[j]);
	}
	CalculateMeshBoundingBox(childrenParentBounds);
}

void BoundingBox::SetCube()
{
	if (viewCube != nullptr)
	{
		delete viewCube;
		viewCube = nullptr;
	}

	viewCube = new Cube(center, Vector3::Zero(), Material(Color::green()), rendererInstance);
	viewCube->transform->SetLocalScale(size);
	viewCube->transform->SetParent(transform);
}
vector<Vector3> BoundingBox::GetBoundsVertices()
{
	vector<Vector3> vertices;
	vertices.push_back(min);
	vertices.push_back(max);
	vertices.push_back(Vector3(min.x, max.y, max.z));
	vertices.push_back(Vector3(max.x, min.y, max.z));
	vertices.push_back(Vector3(min.x, min.y, max.z));
	vertices.push_back(Vector3(min.x, max.y, min.z));
	vertices.push_back(Vector3(max.x, min.y, min.z));
	vertices.push_back(Vector3(max.x, max.y, min.z));
	return vertices;
}

void BoundingBox::Draw()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw();
	}
	if (viewCube != nullptr)
		viewCube->DrawWire();
}

BoundingBox* BoundingBox::GetChild(Transform* childTransform)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->transform == childTransform)
			return children[i];

		BoundingBox* aux = children[i]->GetChild(childTransform);
		if (aux != nullptr)
			return aux;

	}
	return nullptr;
}


Vector3 BoundingBox::GetMin()
{
	return min;
}

Vector3 BoundingBox::GetMax()
{
	return max;
}
