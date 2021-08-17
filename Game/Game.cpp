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

	nc::SetFilePath("../Resources");

	//get font
	int size = 16;
	std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size);

	//create font
	textTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());

	//set font
	textTexture->Create(font->CreateSurface("hello wonderful world", nc::Color{ 1, 1, 1 }));

	//add font
	engine->Get<nc::ResourceSystem>()->Add("textTexture", textTexture);

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("music", "audio/MarioPaint.wav");
	musicChannel = engine->Get<nc::AudioSystem>()->PlayAudio("music", 1, 1, true);

	std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine->Get<nc::Renderer>());

	for (size_t i = 0; i < 10; i++) {
		nc::Transform transform{ {nc::RandomRange(0,800),nc::RandomRange(0,600)}, nc::RandomRange(0,360), 0.25f };
		std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);
		scene->AddActor(std::move(actor));
	}

	//game stuff
	engine->Get<nc::AudioSystem>()->AddAudio("PlayerShoot", "PlayerShoot.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("EnemyShoot", "EnemyShoot.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	stateTimer += engine->time.deltaTime;

	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 5;
		state = eState::StartLevel1;
		break;
	case Game::eState::StartLevel1:

		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::PlayLevel1;
			UpdateLevelStart(engine->time.deltaTime);
		}

		break;
	case Game::eState::StartLevel2:

		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::PlayLevel2;
			UpdateLevel2Start(engine->time.deltaTime);
		}

		break;
	case Game::eState::StartLevelBoss:

		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::PlayLevelBoss;
			UpdateLevelBossStart(engine->time.deltaTime);
		}

		break;
	case Game::eState::Game:
		//if (scene->GetActors<Enemy>().size() == 0)
		//{
		//	state = eState::StartLevel1;
		//}
		break;
	case Game::eState::PlayLevel1:
		//if (scene->GetActors<Enemy>().size() == 0) state = eState::StartLevel2;
		break;
	case Game::eState::PlayLevel2:
		//if (scene->GetActors<Enemy>().size() == 0) state = eState::StartLevelBoss;
		break;
	case Game::eState::PlayLevelBoss:
		//if (scene->GetActors<Enemy>().size() == 0) state = eState::GameOver;
		break;
	case Game::eState::GameOver:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_TAB) == nc::InputSystem::eKeyState::Pressed)
		{
			state = eState::Title;
		}
		break;
	default:
		break;
	}

	engine->Update();
	scene->Update(engine->time.deltaTime);

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Left) == nc::InputSystem::eKeyState::Pressed)
	{
		nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
		//std::cout << position.x << " " << position.y << std::endl;

		//create particles

		engine->Get<nc::ParticleSystem>()->Create(position, 20, 3, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("particle01.png", engine->Get<nc::Renderer>()), 100);
		engine->Get<nc::AudioSystem>()->PlayAudio("explosion", 1, nc::RandomRange(0.2f, 2.0f));
		musicChannel.SetPitch(nc::RandomRange(0.2f, 2.0f));
	}
}

void Game::Draw()
{
	switch (state)
	{
	case Game::eState::Title:
		//graphics.SetColor(nc::Color::red);
		//graphics.DrawString(300, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f), "Centipede(TM)");

		//graphics.SetColor(nc::Color::orange);
		//graphics.DrawString(290, 400, "Press Tab to Play");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel1:
		//graphics.SetColor(nc::Color::orange);
		//graphics.DrawString(300, 300, "Stage 1");

		//graphics.SetColor(nc::Color::purple);
		//graphics.DrawString(290, 400, "Press Tab to Play");
		break;
	case Game::eState::StartLevel2:
		//graphics.SetColor(nc::Color::orange);
		//graphics.DrawString(300, 300, "Stage 2");

		//graphics.SetColor(nc::Color::purple);
		//graphics.DrawString(290, 400, "Press Tab to Play");
		break;
	case Game::eState::StartLevelBoss:
		//graphics.SetColor(nc::Color::orange);
		//graphics.DrawString(300, 300, "Final Stage");

		//graphics.SetColor(nc::Color::purple);
		//graphics.DrawString(290, 400, "Press Tab to Play");
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		//scene->RemoveAllActors();
		//graphics.SetColor(nc::Color::red);
		//graphics.DrawString(290, 400, "Game Over");

		//graphics.SetColor(nc::Color::cyan);
		//graphics.DrawString(300, 300, "Press Tab to Play Again");
		break;
	default:
		break;
	}

	//graphics.SetColor(nc::Color::white);
	//graphics.DrawString(30, 20, std::to_string(score).c_str());
	//graphics.DrawString(750, 20, std::to_string(lives).c_str());

	//draw
	engine->Get<nc::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<nc::Renderer>());
	engine->Draw(engine->Get<nc::Renderer>());

	nc::Transform t;
	t.position = { 30, 30 };
	engine->Get<nc::Renderer>()->Draw(textTexture, t);

	engine->Get<nc::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt)
{
	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	stateFunction = &Game::UpdateLevelStart;
	//	//state = eState::StartGame;
	//}
}

void Game::UpdateLevelStart(float dt)
{
		//std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
		//shape->Load("betterPlayer.txt");

		//std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
		//std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 17, 16, 25 });
		//std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });


		//scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, shape, 300)); // engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("player.txt")

		//for (size_t i = 0; i < 3; i++)
		//{
		//	scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0, 800), nc::RandomRange(0,300)}, nc::RandomRange(0, nc::TwoPi), 2 }, shape2, 30));
		//}
}

void Game::UpdateLevel2Start(float dt)
{
	//std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
	//shape->Load("betterPlayer.txt");

	//std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
	//std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 17, 16, 25 });
	//std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });


	////scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, shape, 300)); // engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("player.txt")

	//for (size_t i = 0; i < 5; i++)
	//{
	//	//add harder enemies
	//	scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0, 800), nc::RandomRange(0,300)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("betterEnemy.txt"), 150));
	//}
}

void Game::UpdateLevelBossStart(float dt)
{
	//std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
	//shape->Load("betterPlayer.txt");

	//std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
	//std::shared_ptr<nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 17, 16, 25 });
	//std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color{ 1, 1, 0 });


	////scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, shape, 300));

	//for (size_t i = 0; i < 10; i++)
	//{
	//	//make few enemies then boss
	//	scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0, 800), nc::RandomRange(0,300)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("evenBetterEnemy.txt"), 300));
	//}
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const nc::Event& event)
{
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	if(lives <= 0)
	{
	state = eState::GameOver;
	}
}

