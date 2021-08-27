#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace nc
{
	class RBPhysicsComponent : public PhysicsComponent
	{
	public:
		void Update() override;
		void ApplyForce(const Vector2& force) override;

	public:
		PhysicsSystem::RigidBodyData data;
		b2Body* body = nullptr;
	};
}