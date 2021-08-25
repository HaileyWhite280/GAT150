#include "PhysicsComponent.h"
#include "Engine.h"

namespace nc
{
	void PhysicsComponent::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= drag;

		acceleration = Vector2::zero;
	}

	//on Read:
	//JSON_READ(value, drag);
}