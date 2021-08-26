#include "Projectiles.h"
#include "Engine.h"

void Projectiles::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) destroy = true;

	transform.position += nc::Vector2::Rotate(nc::Vector2::up, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 15, 2.0f, texture, 20);
}