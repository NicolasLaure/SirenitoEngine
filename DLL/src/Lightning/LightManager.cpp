#include "Lightning\LightManager.h"

LightManager::LightManager()
{
	ambientLight = new GlobalLight(Color(0.05f, 0.05f, 0.05f, 1.0f));
}

LightManager::~LightManager()
{
	if (ambientLight != nullptr)
		delete ambientLight;

	if (directionalLight != nullptr)
		delete directionalLight;

	if (pointLight != nullptr)
		delete pointLight;

	if (spotLight != nullptr)
		delete spotLight;
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

SpotLight* LightManager::GetSpotLight()
{
	return spotLight;
}

void LightManager::SetSpotLight(SpotLight* newLight)
{
	if (spotLight != nullptr)
		delete spotLight;

	spotLight = newLight;
}
