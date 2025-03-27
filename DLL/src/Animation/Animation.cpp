#include "Animation/Animation.h"
#include "Utilities/Time/Time.h"

Animation::Animation(Texture* texture, Vector2 anchorPos, int frameWidth, int frameHeight)
{
	this->texture = texture;
	_isPlaying = false;
	currentIndex = 0;
	CalculateFrames(anchorPos, frameWidth, frameHeight, 1);
	if (frames.size() > 0)
		SetCurrentFrame(currentIndex);
}

Animation::Animation(Texture* texture, Vector2 anchorPos, int frameWidth, int frameHeight, int quantity, float duration, bool canLoop)
{
	this->texture = texture;
	currentIndex = 0;
	this->canLoop = canLoop;
	_duration = duration;

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

void Animation::UpdateAnimation()
{
	if (!_isPlaying)
		return;

	float frameDuration = _duration / frames.size();
	_currentTime = Time::GetTime() - _startTime;
	if (_currentTime > _duration && !canLoop)
	{
		if (currentFrame != frames[frames.size() - 1])
			currentFrame = frames[frames.size() - 1];
		return;
	}

	while (_currentTime > _duration)
	{
		_currentTime -= _duration;
	}

	Frame nextFrame = frames[static_cast<int>(_currentTime / frameDuration)];
	if (currentFrame != nextFrame)
		currentFrame = nextFrame;
}

void Animation::CalculateFrames(Vector2 anchorPos, int frameWidth, int frameHeight, int quantity)
{
	int textureWidth = texture->GetWidth();
	int textureHeight = texture->GetHeight();
	for (int i = 0; i < quantity; i++)
	{
		frames.push_back(Frame(Vector2((anchorPos.x + (frameWidth * i)) / textureWidth, (anchorPos.y + frameHeight) / textureHeight),
			Vector2((anchorPos.x + frameWidth + frameWidth * i) / textureWidth, anchorPos.y / textureHeight)));
	}
}

void Animation::Play()
{
	_isPlaying = true;
	if (_startTime == 0.0f)
		_startTime = Time::GetTime();
	else
		_startTime += Time::GetTime() - _pauseTime;
}

void Animation::Pause()
{
	_isPlaying = false;
	_pauseTime = Time::GetTime();
}
void Animation::Stop()
{
	_isPlaying = false;
	_startTime = 0.0f;
}

void Animation::PlayFromStart()
{
	_isPlaying = true;
	_startTime = Time::GetTime();
}