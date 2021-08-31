#include "RBPhysicsComponent.h"
#include "Engine.h"

namespace nc
{
	RBPhysicsComponent::~RBPhysicsComponent()
	{
		if (body)
		{
			owner->scene->engine->Get<PhysicsSystem>()->DestroyBody(body);
		}
	}

	void RBPhysicsComponent::Update()
	{
		if (!body)
		{
			body = owner->scene->engine->Get<PhysicsSystem>()->CreateBody(owner->transform.position, owner->transform.rotation, data, owner);
		}
		owner->transform.position = PhysicsSystem::WorldToScreen(body->GetPosition());
		owner->transform.rotation = body->GetAngle();
		velocity = body->GetLinearVelocity();
	}

	void RBPhysicsComponent::ApplyForce(const Vector2& force)
	{
		if(body)
		{
			body->ApplyForceToCenter(force, true);
 			body->SetGravityScale(data.gravityScale);
 			body->SetLinearDamping(1);
		}
	}

	//Read
	//JSON_READ(value, data.isDynamic);
	//JSON_READ(value, data.isSensor);
	//JSON_READ(value, data.lockAngle);
	//JSON_READ(value, data.size);
	//JSON_READ(value, data.density);
	//JSON_READ(value, data.friction);
	//JSON_READ(value, data.restitution);
	//JSON_READ(value, data.gravityScale);
}