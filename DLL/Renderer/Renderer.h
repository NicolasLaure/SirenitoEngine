#pragma once

#include "Utilities/Exporter.h"

SIRENITO_API class Renderer
{
private:
	unsigned int buffer;
public:
	SIRENITO_API void Clear();

	void CreateBuffer();
	unsigned int* GetBuffer();
	void SetData(float positions[], int arraySize);
};
