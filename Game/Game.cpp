#include "Game.h"

void Game::Initialize()
{
	//engine create
	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	//scene create
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	//insert the seed thing
	nc::SetFilePath("../Resources");

	//actors
	std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(nc::Transform{ {400, 300}, 0, 1 });
	{
	std::unique_ptr<nc::SpriteComponent> component = std::make_unique<nc::SpriteComponent>();
	component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine->Get<nc::Renderer>());
	actor->AddComponent(std::move(component));
	}
	{
		std::unique_ptr<nc::PhysicsComponent> component = std::make_unique<nc::PhysicsComponent>();
		component->AppyForce(nc::Vector2::right * 200);
	}

	scene->AddActor(std::move(actor));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();

	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}

