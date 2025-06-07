#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/Transform.h"
#include "Utilities/Color.h"

SIRENITO_API class BaseLight
{
public:
	Transform transform;
	Color color;
};