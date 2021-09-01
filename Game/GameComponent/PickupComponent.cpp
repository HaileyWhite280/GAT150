#include "PickupComponent.h"
#include "Engine.h"

using namespace nc;

PickupComponent::~PickupComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collisionEnter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collisionExit", owner);
}

void PickupComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collisionEnter", std::bind(&PickupComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	//owner->scene->engine->Get<EventSystem>()->Subscribe("collisionExit", std::bind(&PickupComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

void PickupComponent::Update()
{

}

void PickupComponent::OnCollisionEnter(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Player")) {
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("coin");
		owner->destroy = true;

		Event event;
		event.name = "addScore";
		event.data = 10;

		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}
}

void PickupComponent::OnCollisionExit(const nc::Event& event)
{

}


bool PickupComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PickupComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}


