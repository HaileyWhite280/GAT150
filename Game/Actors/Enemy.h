#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	//Enemy(const nc::Transform& transform, float speed) : nc::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float speed = 300;
	float fireTimer = 0;
	float fireRate = 2;
};
