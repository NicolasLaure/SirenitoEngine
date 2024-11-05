#include "Animation/Animation.h"

Animation::Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, bool canLoop)
{
	this->texture = texture;
	currentIndex = 0;
	this->canLoop = canLoop;
	CalculateFrames(anchorPos, frameWidth, frameHeight, 1);
	if (frames.size() > 0)
		SetCurrentFrame(currentIndex);
}

Animation::Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, int quantity, bool canLoop)
{
	this->texture = texture;
	currentIndex = 0;
	this->canLoop = canLoop;
	CalculateFrames(anchorPos, frameWidth, frameHeight, quantity);
	if (frames.size() > 0)
		SetCurrentFrame(currentIndex);
}

void Animation::SetCanLoop(bool value)
{
	canLoop = value;
}

void Animation::SetCurrentFrame(int index)
{
	currentFrame = frames[index];
}

void Animation::NextFrame()
{
	if (currentIndex + 1 < frames.size())
		currentIndex++;
	else
	{
		if (canLoop)
			currentIndex = 0;
	}

	currentFrame = frames[currentIndex];
}

void Animation::CalculateFrames(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity)
{
	int textureWidth = texture->GetWidth();
	int textureHeight = texture->GetHeight();
	for (int i = 0; i < quantity; i++)
	{
		frames.push_back(Frame({ (anchorPos.x + frameWidth * i) / textureWidth, anchorPos.y / textureHeight },
			{ (anchorPos.x + frameWidth + (frameWidth * i)) / textureWidth, (anchorPos.y + frameHeight) / textureHeight }));
	}
}