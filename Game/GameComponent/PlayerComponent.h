#pragma once
#include "Component/Component.h"
#include "Framework/EventSystem.h"
#include <list>

//JSON_READ (value, speed)
class PlayerComponent : public nc::Component
{
public:

public:
	float speed = 0;

	void Create() override;

	// Inherited via Component
	virtual void Update() override;

	virtual void OnCollisionEnter(const nc::Event& event) {}
	virtual void OnCollisionExit(const nc::Event& event) {}

	// Inherited via Serializable
	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

private:
	std::list<nc::Actor*> contacts;
};