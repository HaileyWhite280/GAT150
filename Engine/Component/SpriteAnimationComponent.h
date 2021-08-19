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

		float frameTimer = 0;
		float frameTime = 0;

		SDL_Rect rect;
	};
}