#include "Player.h"
#include "Projectiles.h"
#include "Engine.h"
#include "Enemy.h"
#include <memory>

Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture }, speed{ speed }
{

}

void Player::Initialize()
{
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ -8 , 0 }; //position of projectile
	locator->transform.localRotation = nc::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0 , 5 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0 , -5 };
	AddChild(std::move(locator));

	scene->engine->Get<nc::AudioSystem>()->AddAudio("PlayerShoot", "Audio/PlayerShoot.wav");
	scene->engine->Get<nc::AudioSystem>()->AddAudio("explosion", "Audio/explosion.wav");
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	float thrust = 0;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::Held) transform.rotation -= -5 * dt;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::Held) transform.rotation -= 5 * dt;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::Held) thrust = speed;
	if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_LSHIFT) == nc::InputSystem::eKeyState::Held) thrust *= 2;


	nc::Vector2 acceleration = nc::Vector2::Rotate(nc::Vector2::up, transform.rotation) * thrust;
	velocity += acceleration * dt;

	velocity *= 0.99f;

	transform.position += velocity * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	fireTimer -= dt;
	immunityTime -= dt;
	if (fireTimer <= 0 && scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Held)
	{
		fireTimer = fireRate;
		std::shared_ptr<nc::Texture> projectileTexture = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle01.png", scene->engine->Get<nc::Renderer>());

		{
			nc::Transform t = transform;
			t.scale = 0.5f;
			t.position = transform.position + 50;

			std::unique_ptr<Projectiles> projectile = std::make_unique<Projectiles>(t, projectileTexture, 200);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}

		//double bullets
		{
			nc::Transform t = transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectiles> projectile = std::make_unique<Projectiles>(t, projectileTexture, 200);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
		}

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("PlayerShoot");

	}

	//scene->engine->Get<nc::ParticleSystem>()->Create(children[1]->transform.position, 3, 2, colors , 50, children[1]->transform.rotation, nc::DegToRad(30));
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) && immunityTime <= 0)
	{
		//destroy = true;

		std::shared_ptr<nc::Texture> explosionTexture = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png", scene->engine->Get<nc::Renderer>());
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, explosionTexture, 3);

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes I died");
		scene->engine->Get<nc::EventSystem>()->Notify(event);
		immunityTime = immuneRate;
	}
}
