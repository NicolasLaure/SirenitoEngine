#include "Lightning\LightManager.h"

LightManager::LightManager()
{
	ambientLight = new GlobalLight(Color(0.05f, 0.05f, 0.05f, 1.0f));
	directionalLight = new DirectionalLight(Color(0.6f, 0.6f, 0.6f, 1.0f), Vector3(-75.0f, 90.0f, 0.0f));
}

LightManager::~LightManager()
{
	if (ambientLight != nullptr)
		delete ambientLight;
}

GlobalLight* LightManager::GetAmbientLight()
{
	return ambientLight;
}

void LightManager::SetAmbientLight(GlobalLight* newLight)
{
	if (ambientLight != nullptr)
		delete ambientLight;

	ambientLight = newLight;
}

PointLight* LightManager::GetPointLight()
{
	return pointLight;
}

void LightManager::SetPointLight(PointLight* newLight)
{
	if (pointLight != nullptr)
		delete pointLight;

	pointLight = newLight;
}

DirectionalLight* LightManager::GetDirectionalLight()
{
	return directionalLight;
}

void LightManager::SetDirectionalLight(DirectionalLight* newLight)
{
	if (directionalLight != nullptr)
		delete directionalLight;

	directionalLight = newLight;
}
