#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity3D/Model.h"
#include "Frustum.h"

SIRENITO_API class FrustumCulling
{
public:
	static void ShouldDraw(Frustum* frustum, Model* model)
	{
		for (int i = 0; i < model->children.size(); i++)
		{
			ShouldDraw(frustum, model->children[i]);
		}

		if (model->boundingBox == nullptr)
		{
			model->shouldDraw = true;
			return;
		}

		vector<Vector3> compoundBox = model->boundingBox->GetCompoundBoundsVertices();

		int verticesInside = 0;
		for (int i = 0; i < compoundBox.size(); i++)
		{
			if (frustum->IsPointInside(compoundBox[i]))
			{
				verticesInside++;
			}
		}
		if (verticesInside == compoundBox.size() - 1)
		{
			model->shouldDraw = true;
		}
		else if (verticesInside == 0)
			model->shouldDraw = false;
		else
		{
			vector<Vector3> localBox = model->boundingBox->GetTransformedBoundsVertices();
			for (int i = 0; i < localBox.size(); i++)
			{
				if (frustum->IsPointInside(localBox[i]))
				{
					model->shouldDraw = true;
					return;
				}
			}
			model->shouldDraw = false;
		}
	}
};