#include "PlayerComponent.h"
#include "Engine.h"

using namespace nc;

PlayerComponent::~PlayerComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collisionEnter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collisionExit", owner);
}

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "audio/hurt.wav");
	//owner->scene->engine->Get<AudioSystem>()->AddAudio("jump", "audio/jump.mp3");
}

void PlayerComponent::Update()
{
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
	}
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
	}
	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_W) == InputSystem::eKeyState::Pressed)
	{
		//owner->scene->engine->Get<AudioSystem>()->PlayAudio("jump");
		force.y -= 400;
	}


	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);
	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (physicsComponent->velocity.x > 0) { spriteAnimationComponent->SetSequence("walk_left"); }
	else if(physicsComponent->velocity.x < 0) { spriteAnimationComponent->SetSequence("walk_right"); }
}

void PlayerComponent::OnCollisionEnter(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "ground")) {
		contacts.push_back(actor);
	}

	if (istring_compare(actor->tag, "enemy")) {
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
	}

	//if (istring_compare(actor->tag, "pickup")) {
	//	owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
	//	actor->destroy = true;
	//}
}

void PlayerComponent::OnCollisionExit(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "ground")) {
		contacts.remove(actor);
	}
}


bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);

	return true;
}
