#pragma once
#include "Engine.h"

namespace nc
{
	class SpriteAnimationComponent : public SpriteComponent, public Serializable
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

		// Inherited via Serializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}