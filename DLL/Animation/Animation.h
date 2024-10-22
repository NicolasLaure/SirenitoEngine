#pragma once
#include <vector>
#include "Utilities/Exporter.h"
#include "Textures/Texture.h"
#include "Utilities/Vector2.h"
#include "Animation/Frame.h"

SIRENITO_API class Animation
{
private:
	std::vector<Frame> frames;

	void CalculateFrames(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity);
public:

	Animation(Vector2f anchorPos, int frameWidth, int frameHeight);
	Animation(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity);

	Frame GetFrame(int index);
	std::vector<Frame> GetFrames();
};