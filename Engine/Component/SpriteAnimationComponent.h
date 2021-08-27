#pragma once
#include "Engine.h"

namespace nc
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer* renderer) override;

	public:
		int frame = 0;
		int fps = 0;

		int numFramesX = 0;
		int numFramesY = 0;

		int startFrame = 0;
		int endFrame = 0;

		float frameTimer = 0;
		float frameTime = 0;

		SDL_Rect rect;
	};

	//Read: SpriteComponent::Read(value);
	// 	   JSON_READ fps, numframes, startframe, endframe
	// 
	// 	   if(startFrame = 0 && endFrame == 0) endFrame = numFramesX * numFramesY;
	// 	   frame = startFrame;
	//return true;
}