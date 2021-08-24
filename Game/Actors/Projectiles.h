#pragma once
#include "Object/Actor.h"

class Projectiles : public nc::Actor
{
public:
	Projectiles(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 1 };
	float speed = 300;
};