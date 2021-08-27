#include "PlayerComponent.h"
#include "Engine.h"

using namespace nc;

//Update:
//PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
//assert(physicsComponent);
// physicsComponent->AppyForce(force);
// 
//Vector2 force = Vector2::zero;
// 
//if(owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
//{
//force.x -= speed;
//}
//MAKE FOR SCANCODE D and copy if to READ

void PlayerComponent::Update()
{
	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);
	physicsComponent->AppyForce(force);

	Vector2 force = Vector2::zero;
 
	if(owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
	force.x -= speed;
	}

	if(owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
	force.y -= speed;
	}
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	return false;
}
