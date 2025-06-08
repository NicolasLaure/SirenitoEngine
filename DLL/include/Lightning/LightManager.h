#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/GlobalLight.h"
#include "Lightning/PointLight.h"

SIRENITO_API class LightManager
{
private:
	GlobalLight* ambientLight = nullptr;
	PointLight* pointLight = nullptr;

public:
	SIRENITO_API LightManager();
	SIRENITO_API ~LightManager();

	SIRENITO_API GlobalLight* GetAmbientLight();
	SIRENITO_API void SetAmbientLight(GlobalLight* newLight);

	SIRENITO_API PointLight* GetPointLight();
	SIRENITO_API void SetPointLight(PointLight* newLight);
};