#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/GlobalLight.h"

SIRENITO_API class LightManager
{
private:
	GlobalLight* ambientLight = nullptr;

public:
	SIRENITO_API LightManager();
	SIRENITO_API ~LightManager();

	SIRENITO_API GlobalLight* GetAmbientLight();
	SIRENITO_API void SetAmbientLight(GlobalLight* newLight);
};