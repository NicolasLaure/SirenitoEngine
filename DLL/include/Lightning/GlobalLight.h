#pragma once
#include "Utilities/Exporter.h"
#include "Lightning/BaseLight.h"

SIRENITO_API class GlobalLight : public BaseLight
{
public:
	SIRENITO_API GlobalLight(Color color);
};