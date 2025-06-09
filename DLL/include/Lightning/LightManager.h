#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/GlobalLight.h"
#include "Lightning/PointLight.h"
#include "Lightning/DirectionalLight.h"
#include "Lightning/SpotLight.h"

SIRENITO_API class LightManager
{
private:
	GlobalLight* ambientLight = nullptr;
	PointLight* pointLight = nullptr;
	DirectionalLight* directionalLight = nullptr;
	SpotLight* spotLight = nullptr;

public:
	SIRENITO_API LightManager();
	SIRENITO_API ~LightManager();

	SIRENITO_API GlobalLight* GetAmbientLight();
	SIRENITO_API void SetAmbientLight(GlobalLight* newLight);

	SIRENITO_API PointLight* GetPointLight();
	SIRENITO_API void SetPointLight(PointLight* newLight);

	SIRENITO_API DirectionalLight* GetDirectionalLight();
	SIRENITO_API void SetDirectionalLight(DirectionalLight* newLight);

	SIRENITO_API SpotLight* GetSpotLight();
	SIRENITO_API void SetSpotLight(SpotLight* newLight);
};