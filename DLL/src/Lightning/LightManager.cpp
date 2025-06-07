#include "Lightning\LightManager.h"

LightManager::LightManager()
{
	ambientLight = new GlobalLight(Color(0.1f, 0.1f, 0.1f, 1.0f));
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
