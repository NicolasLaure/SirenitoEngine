#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Model.h"
#include "Utilities/Plane.h"
#include "Renderer/Renderer.h"
#include "Camera/Camera.h"

SIRENITO_API class Scene
{
private:
	Model* sceneModel;
	Camera* camera;
	vector<Model*> models;
	vector<Model*> planeModels;
	vector<Self_Plane> planes;

	SIRENITO_API bool IsPointInside(Vector3 point);
public:

	SIRENITO_API Scene(const char* sceneModelPath, Camera* camera, Renderer* rendererInstance);

	SIRENITO_API void ShouldDraw(Model* model);
	SIRENITO_API void Draw();
	SIRENITO_API void SetScale(Vector3 scale);
	SIRENITO_API Model* GetModel(const char* name);
};
