#include "Animation.h"

Animation::Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, bool canLoop)
{
	this->texture = texture;
	currentIndex = 0;
	this->canLoop = canLoop;
	CalculateFrames(anchorPos, frameWidth, frameHeight, 1);
}

Animation::Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, int quantity, bool canLoop)
{
	this->texture = texture;
	currentIndex = 0;
	this->canLoop = canLoop;
	CalculateFrames(anchorPos, frameWidth, frameHeight, quantity);
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

}

void Animation::CalculateFrames(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity)
{
	for (int i = 0; i < quantity; i++)
	{
		frames.push_back(Frame({ (anchorPos.x + frameWidth * i) / texture->GetWidth(), anchorPos.y / texture->GetHeight() },
			{ (anchorPos.x + frameWidth + frameWidth * i) / texture->GetWidth(), (anchorPos.y + frameHeight) / texture->GetHeight() }));
	}
}
