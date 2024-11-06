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
	bool canLoop;
	Texture* texture;
	bool _isPlaying;
	float _startTime;
	float _pauseTime;
	float _currentTime;
	float _duration;
	Frame _previousFrame;

	SIRENITO_API void CalculateFrames(Vector2f anchorPos, int frameWidth, int frameHeight, int quantity);
public:
	Frame currentFrame;
	int currentIndex;

	SIRENITO_API Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, bool canLoop);
	SIRENITO_API Animation(Texture* texture, Vector2f anchorPos, int frameWidth, int frameHeight, int quantity, float duration, bool canLoop);

	SIRENITO_API void SetCanLoop(bool value);
	SIRENITO_API void SetCurrentFrame(int index);
	SIRENITO_API void NextFrame();
	SIRENITO_API void UpdateAnimation();
	SIRENITO_API void Play();
	SIRENITO_API void Pause();
	SIRENITO_API void Stop();
	SIRENITO_API void PlayFromStart();
};