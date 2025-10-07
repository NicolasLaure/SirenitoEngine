#include "Collisions/BSP_scene/Scene.h"
#include <iostream>

using namespace std;

bool Scene::IsPointInside(Vector3 point)
{
	for (int i = 0; i < planes.size(); i++)
	{
		if (!planes[i].GetSide(point))
			return false;
	}
	return true;
}

Scene::Scene(const char* sceneModelPath, Renderer* rendererInstance)
{
	sceneModel = new Model(sceneModelPath, rendererInstance);

	for (int i = 0; i < sceneModel->children.size(); i++)
	{
		if (sceneModel->children.at(i)->transform->GetName().find("Plane") != string::npos)
		{
			planeModels.push_back(sceneModel->children.at(i));

			Mesh* mesh = sceneModel->children.at(i)->meshes->at(0);
			Self_Plane plane = Self_Plane(mesh->vertices);
			cout << "Plane Normal: " << plane.GetNormal().ToString() << " Position: " << plane.GetDistance() << endl;
			planes.push_back(plane);
		}
		else
			models.push_back(sceneModel->children.at(i));
	}
}

bool Scene::ShouldDraw(Model* model)
{
	if (model->boundingBox == nullptr)
		return true;

	vector<Vector3> vertices = model->boundingBox->GetTransformedBoundsVertices();

	for (int i = 0; i < vertices.size(); i++)
	{
		if (IsPointInside(vertices[i]))
			return true;
	}

	return false;
}

void Scene::Draw()
{
	for (int i = 0; i < planes.size(); i++)
	{
		planeModels[i]->Draw();
	}

	for (int i = 0; i < models.size(); i++)
	{
		models[i]->Draw();
	}
}

void Scene::SetScale(Vector3 scale)
{
	sceneModel->transform->SetLocalScale(scale);
}

Model* Scene::GetModel(const char* name)
{
	for (int i = 0; i < models.size(); i++)
	{
		cout << "Model Name: " << models[i]->transform->GetName();

		if (models[i]->transform->GetName() == name)
			return models[i];
	}
	return nullptr;
}
