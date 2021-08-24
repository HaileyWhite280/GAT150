#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		void Update() override;
		void ApplyForce(const Vector2& force) { acceleration += force; }

		//TODO impliment from Serializable here and in SpriteAnimationComponent and SpriteComponent

	public:
		Vector2 velocity;
		Vector2 force;
		Vector2 acceleration;
	};
}
