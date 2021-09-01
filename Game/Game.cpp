#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"

void Game::Initialize()
{
    //create engine
    engine = std::make_unique<nc::Engine>();
    engine->Startup();
    engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

    //register classes
    REGISTER_CLASS(PlayerComponent);
    REGISTER_CLASS(EnemyComponent);
    REGISTER_CLASS(PickupComponent);

    //create scene
    scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();

    nc::SetFilePath("../Resources");

    rapidjson::Document document;
    bool success = nc::json::Load("scene.txt", document);
    scene->Read(document);
    assert(success);

    nc::TileMap tilemap;
    tilemap.scene = scene.get();

    success = nc::json::Load("map.txt", document);
    assert(success);
    tilemap.Read(document);
    tilemap.Create();

    //for (int i = 0; i < 10; i++)
    //{
    //    auto actor = nc::ObjectFactory::Instance().Create<nc::Actor>("Bat");
    //    actor->transform.position = nc::Vector2{ nc::RandomRange(0,800), nc::RandomRange(400,500) };
    //    scene->AddActor(std::move(actor));
    //}
}

void Game::Shutdown()
{
    scene->RemoveAllActors();
    engine->Shutdown();
}

void Game::Update()
{
    engine->Update();

    //update
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