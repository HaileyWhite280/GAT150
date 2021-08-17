#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Component/Component.h"
#include <memory>
#include <vector>

namespace nc
{
	class Scene;
	class Renderer;

	class Actor : public Object
	{
	public:
		Actor() {}
		Actor(const Transform& transform) : transform{ transform } {}

		virtual void Initialize() {}

		virtual void Update(float dt);
		virtual void Draw(Renderer* renderer);
		
		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		void AddChild(std::unique_ptr<Actor> actor);

		void AddComponent(std::unique_ptr<Component> component);

	public:
		bool destroy = false;
		std::string tag;

		Transform transform;
		Scene* scene{nullptr};

		Actor* parent{ nullptr };
		std::vector<std::unique_ptr<Actor>> children;

		std::vector<std::unique_ptr<Component>> components;
	};
}