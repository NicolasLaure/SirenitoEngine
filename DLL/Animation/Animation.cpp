#include "Animation.h"

Animation::Animation(Vector2f anchorPos, int frameWidth, int frameHeight)
{
	this->texture = texture;
	CalculateFrames(anchorPos, frameWidth, frameHeight, 1);
}

Animation::Animation(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity)
{
	this->texture = texture;
	CalculateFrames(anchorPos, frameWidth, frameHeight, quantity);
}

Frame Animation::GetFrame(int index)
{
	return frames[i];
}

std::vector<Frame> Animation::GetFrames()
{
	return frames;
}

void Animation::CalculateFrames(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		frames.push_back(Frame(texture, { anchorPos.x + frameWidth * i, anchorPos.y }, { anchorPos.x + frameWidth + frameWidth * i, anchorPos.y + frameHeight }));
	}
}
