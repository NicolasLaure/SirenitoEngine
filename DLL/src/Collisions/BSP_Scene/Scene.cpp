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

void Scene::ShouldDraw(Model* model)
{
	for (int i = 0; i < model->children.size(); i++)
	{
		ShouldDraw(model->children[i]);
	}

	if (model->boundingBox == nullptr)
	{
		model->shouldDraw = true;
		return;
	}

	vector<Vector3> compoundBox = model->boundingBox->GetCompoundBoundsVertices();

	int verticesInside = 0;
	for (int i = 0; i < compoundBox.size(); i++)
	{
		if (IsPointInside(compoundBox[i]))
		{
			verticesInside++;
		}
	}
	if (verticesInside == compoundBox.size() - 1)
	{
		model->shouldDraw = true;
	}
	else if (verticesInside == 0)
		model->shouldDraw = false;
	else
	{
		vector<Vector3> localBox = model->boundingBox->GetTransformedBoundsVertices();
		for (int i = 0; i < localBox.size(); i++)
		{
			if (IsPointInside(localBox[i]))
			{
				model->shouldDraw = true;
				return;
			}
		}
		model->shouldDraw = false;
	}
}

void Scene::Draw()
{
	for (int i = 0; i < planes.size(); i++)
	{
		planeModels[i]->Draw();
	}

	for (int i = 0; i < models.size(); i++)
	{
		ShouldDraw(models[i]);
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
