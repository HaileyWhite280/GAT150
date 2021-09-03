#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"
#include "Engine.h"

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

    nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    nc::SetFilePath("../Resources");

    scene->engine->Get<nc::AudioSystem>()->AddAudio("music", "audio/MarioPaint.mp3");
    scene->engine->Get<nc::AudioSystem>()->PlayAudio("music", 0.05f, 1.0f, true);

    engine->Get<nc::EventSystem>()->Subscribe("addScore", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
    engine->Get<nc::EventSystem>()->Subscribe("getTimer", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
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

    switch (state)
    {
    case Game::eState::Reset:
        Reset();
        break;
    case Game::eState::Title:
        Title();
        break;
    case Game::eState::StartGame:
        StartGame();
        break;
    case Game::eState::StartLevel:
        StartLevel();
        break;
    case Game::eState::Level:
        Level();
        break;
    case Game::eState::PlayerDead:
        PlayerDead();
        break;
    case Game::eState::GameOver:
        GameOver();
        break;
    default:
        break;
    }

    //update score
    auto scoreActor = scene->FindActor("Score");
    if (scoreActor)
    {
        scoreActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(score));
    }

    auto timerActor = scene->FindActor("Timer");
    if (timerActor)
    {
        timerActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(GetTimer()));
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

void Game::Reset()
{
    scene->RemoveAllActors();

    rapidjson::Document document;
    bool success = nc::json::Load("Json/title.txt", document);
    assert(success);
    scene->Read(document);

    state = eState::Title;
}

void Game::Title()
{
    if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
    {
        auto title = scene->FindActor("Title");
        auto title2 = scene->FindActor("Title2");

        title->active = false;
        title2->active = false;

        state = eState::StartGame;
    }
    scene->Update(engine->time.deltaTime);
}

void Game::StartGame()
{
    rapidjson::Document document;
    bool success = nc::json::Load("Json/scene.txt", document);
    assert(success);
    scene->Read(document);

    success = nc::json::Load("Json/blocks.txt", document);
    assert(success);
    scene->Read(document);

    success = nc::json::Load("Json/score.txt", document);
    assert(success);
    scene->Read(document);

    std::string getMap = "";

    std::string map1 = "Json/map1.txt";
    std::string map2 = "Json/map2.txt";
    std::string map3 = "Json/map3.txt";
    std::string map4 = "Json/map4.txt";

    int random = nc::RandomRange(1, 4);

    switch (random)
    {
    case 1:
        getMap = map1;
        break;
    case 2:
        getMap = map2;
        break;
    case 3:
        getMap = map3;
        break;
    case 4:
        getMap = map4;
        break;
    default:
        break;
    }

    std::cout << getMap << std::endl;

    nc::TileMap tilemap;
    tilemap.scene = scene.get();
    success = nc::json::Load(map4, document);
    assert(success);
    tilemap.Read(document);
    tilemap.Create();

    state = eState::StartLevel;
    stateTimer = 0;
}

void Game::StartLevel()
{
    stateTimer += engine->time.deltaTime;
    if (stateTimer >= 1)
    {
        auto player = nc::ObjectFactory::Instance().Create<nc::Actor>("Player");
        player->transform.position = { 60 , 550 };
        scene->AddActor(std::move(player));

        spawnTimer = 2;
        state = eState::Level;
    }

}

void Game::Level()
{
    spawnTimer -= engine->time.deltaTime;
    gameTimer += engine->time.deltaTime;
    nc::Actor* coin = scene->FindActor("Coin");

    //random coin spawn
    if (!coin)
    {
        spawnTimer = 120;
                
        auto coin = nc::ObjectFactory::Instance().Create<nc::Actor>("Coin");
        coin->transform.position = { nc::RandomRange(100, 700), nc::RandomRange(100, 500) };
        scene->AddActor(std::move(coin));
    }

    coin = scene->FindActor("Coin");
    if (!coin)
    {
        gameTimer = 0;
        scene->RemoveAllActors();
        state = eState::StartGame;
    }

    //Player dies in 20 seconds WORKS
    if (gameTimer >= 20)
    {
        state = eState::PlayerDead;
        std::cout << "playerDead" << std::endl;

        std::cout << gameTimer << std::endl;
    }


}

void Game::PlayerDead()
{
    scene->RemoveAllActors();

    state = eState::GameOver;
}

void Game::GameOver()
{
    rapidjson::Document document;
    bool success = nc::json::Load("Json/gameOver.txt", document);
    assert(success);
    scene->Read(document);

    if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
    {
        state = eState::Reset;
    }
}

void Game::OnAddScore(const nc::Event& event)
{
    score += std::get<int>(event.data);
}

float Game::GetTimer()
{
    return (gameTimer - 20) * -1;
}

