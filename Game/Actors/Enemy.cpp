#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "Projectiles.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>())
	{
		nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);

		float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);

		transform.rotation = nc::Lerp(transform.rotation, transform.rotation + turnAngle, 2 * dt);


		float angle = nc::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		if (fireTimer <= 0)
		{
			fireTimer = fireRate;
			std::shared_ptr<nc::Texture> projectileTexture = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle01.png", scene->engine->Get<nc::Renderer>());

			nc::Transform t = transform;
			t.scale = 0.5;

			std::unique_ptr<Projectiles> projectile = std::make_unique<Projectiles>(t, projectileTexture, 200);
			projectile->tag = "Enemy";
			scene->AddActor(std::move(projectile));
		}

		scene->engine->Get<nc::AudioSystem>()->AddAudio("EnemyShoot", "Audio/EnemyShoot.wav");
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("EnemyShoot");
	}

	transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectiles*>(actor) && actor->tag == "Player")
	{
		destroy = true;

		std::shared_ptr<nc::Texture> explosionTexture = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png", scene->engine->Get<nc::Renderer>());
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 1, explosionTexture, 3);


		scene->engine->Get<nc::AudioSystem>()->AddAudio("explosion", "Audio/explosion.wav");
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}
}

