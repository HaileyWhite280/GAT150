#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace nc
{
	class RBPhysicsComponent : public PhysicsComponent
	{
		//copy first public from PhysicsComponent.h

		//change ApplyForce to remove {} add override and in PhysicsComponent make it virtual

	public:
		PhysicsSystem::RigidBodyData data;
		b2Body* body = nullptr;
	};
}