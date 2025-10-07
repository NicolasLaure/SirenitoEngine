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
		min = transform->GetPosition();
		max = transform->GetPosition();
		return;
	}

	min = Vector3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	max = Vector3(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

	for (int i = 0; i < vertexList.size(); i++)
	{
		min = Vector3::Min(min, vertexList[i]);
		max = Vector3::Max(max, vertexList[i]);
	}
}

void BoundingBox::CalculateMeshBoundingBox(vector<Vertex> vertexList)
{
	if (vertexList.size() == 0)
	{
		center = transform->GetPosition();
		min = transform->GetPosition();
		max = transform->GetPosition();
		return;
	}

	min = Vector3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	max = Vector3(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

	for (int i = 0; i < vertexList.size(); i++)
	{
		min = Vector3::Min(min, vertexList[i].Position);
		max = Vector3::Max(max, vertexList[i].Position);
	}
}

void BoundingBox::CalculateCompoundBoundingBox()
{
	compoundMin = Vector3::Min(transform->TransformPoint(min), transform->TransformPoint(max));
	compoundMax = Vector3::Max(transform->TransformPoint(min), transform->TransformPoint(max));

	if (children.size() < 1)
	{
		size = compoundMax - compoundMin;
		center = (compoundMax + compoundMin) * 0.5f;
		return;
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->CalculateCompoundBoundingBox();

		compoundMin = Vector3::Min(compoundMin, children[i]->compoundMax);
		compoundMin = Vector3::Min(compoundMin, children[i]->compoundMin);

		compoundMax = Vector3::Max(compoundMax, children[i]->compoundMin);
		compoundMax = Vector3::Max(compoundMax, children[i]->compoundMax);
	}

	size = compoundMax - compoundMin;
	center = (compoundMax + compoundMin) * 0.5f;
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
}
vector<Vector3> BoundingBox::GetTransformedBoundsVertices()
{
	vector<Vector3> vertices;
	vertices.push_back(transform->TransformPoint(min));
	vertices.push_back(transform->TransformPoint(max));
	vertices.push_back(transform->TransformPoint(Vector3(min.x, max.y, max.z)));
	vertices.push_back(transform->TransformPoint(Vector3(max.x, min.y, max.z)));
	vertices.push_back(transform->TransformPoint(Vector3(min.x, min.y, max.z)));
	vertices.push_back(transform->TransformPoint(Vector3(min.x, max.y, min.z)));
	vertices.push_back(transform->TransformPoint(Vector3(max.x, min.y, min.z)));
	vertices.push_back(transform->TransformPoint(Vector3(max.x, max.y, min.z)));
	return vertices;
}

void BoundingBox::Draw()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw();
	}
	SetCube();
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
