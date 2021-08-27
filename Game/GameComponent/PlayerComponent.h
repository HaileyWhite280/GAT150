#pragma once
#include "Component/Component.h"

//JSON_READ (value, speed)
class PlayerComponent : public nc::Component, public Serializable
{
public:

public:
	float speed = 0;

	// Inherited via Component
	virtual void Update() override;

	// Inherited via Serializable
	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
};