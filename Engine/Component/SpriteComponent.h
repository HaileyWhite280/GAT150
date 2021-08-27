#pragma once
#include "GraphicsComponent.h"
#include <memory>

namespace nc
{
	class Texture;

	class SpriteComponent : public GraphicsComponent, public Serializable
	{
	public:
		void Update() override;
		void Draw(Renderer* renderer) override;

	public:
		std::shared_ptr<Texture> texture;

		// Inherited via Serializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};
}