#include "RBPhysicsComponent.h"
#include "Engine.h"

namespace nc
{
	//ApplyForce
	//if(body)
	//{
	//body->ApplyForceToCenter(force, true);
	// 	   body->SetGravityScale(data.gravityScale);
	// 	   body->SetLinearDamping(1); //Might be changed to Drag
	//}

	//Update
	//if(!body)
	//{
	//body = owner->scene->engine->Get<PhysicsSystem>()->CreateBody(owner->transform.position, owner->transform.rotation, data, owner);
	//}
	//owner->transform.position = PhysicsSystem::WorldToScreen(body->GetPosition());
	//owner->transform.rotation = body->GetAngle();
	//velocity = body->GetLinearVelocity();

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