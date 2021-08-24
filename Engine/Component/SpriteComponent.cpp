#include "SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Object/Actor.h"
#include "Engine.h"

namespace nc
{
	void nc::SpriteComponent::Update()
	{
		//
	}

	void nc::SpriteComponent::Draw(Renderer* renderer)
	{
		renderer->Draw(texture, owner->transform);
	}

	//Read: std::string textureName;
	//JSON_READ(value, textureName);
	//texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>(textureName, owner->scene->engine->Get<Renderer>());
	//return true
}
