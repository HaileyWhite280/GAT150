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

//OnCollisions need to be in here

//Enter:
//void* p = std::get<void*>(event.data);
//Actor* actor = reinterpret_cast<Actor*>(p);
// if(istring_compare(actor->tag == "ground"))
// {contacts.push_back(actor);}
//std::cout << actor->tag << std::endl;
// if(istring_compare(actor->tag, "enemy))
// {owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt");}
//	

//copy paste Enter to Exit
//Exit
//contacts.remove(actor);

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "Audio/hurt.wav");
}

void PlayerComponent::Update()
{
	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);
	physicsComponent->AppyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);
	if (physicsComponent->velocity.x > 0) spriteAnimationComponent->SetSequence("walk_right");
	else if (physicsComponent->velocity.x < 0) spriteAnimationComponent->SetSequence("walk_left");
	else spriteAnimationComponent->SetSequence("idle");

	Vector2 force = Vector2::zero;
 
	//walk left
	if(owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
	force.x -= speed;
	}

	//walk right
	if(owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
	force.x += speed;
	}

	//jump
	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)
	{
		force.y -= 200;
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
