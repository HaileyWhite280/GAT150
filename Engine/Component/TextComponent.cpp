#include "TextComponent.h"

namespace nc
{
	void TextComponent::Update()
	{

	}

	void TextComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, owner->transform);
	}

	void TextComponent::SetText(const std::string& text)
	{
		texture->Create(font->CreateSurface(text, color));
	}

	bool TextComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool TextComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(fontName);
		JSON_READ(fontSize);
		JSON_READ(color);
		JSON_READ(text);

		font = engine->Get<ResourceSystem>()->Get<Font>(fontName, &fontSize);
		texture = engine->Get<ResourceSystem>()->Get<Texture>("texture", engine->Get<Renderer>());

		SetText(text);

		return true;
	}
}