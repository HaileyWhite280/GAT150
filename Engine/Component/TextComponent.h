#pragma once
#include "Engine.h"
#include <string>

namespace nc
{
	class Texture;
	class Font;

	class TextComponent : public GraphicsComponent
	{
	public:
		virtual void Update() override;
		virtual void Draw(Renderer* renderer) override;

		void SetText(const std::string& text);

		//write and read
		bool Write(const rapidjson::Value& value) const;
		bool Read(const rapidjson::Value& value);

	public:
		std::string fontName;
		int fontSize;
		Color color;
		std::string text;

		shared_ptr<Font> font;
		shared_ptr<Texture> texture;
	};
}