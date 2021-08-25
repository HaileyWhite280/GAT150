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

	//add Sounds
	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "Audio/explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("PlayerShoot", "Audio/PlayerShoot.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("EnemyShoot", "Audio/EnemyShoot.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("MarioMusic", "Audio/MarioPaint.MP3");
	musicChannel = engine->Get<nc::AudioSystem>()->PlayAudio("MarioMusic", 1, 1, true);

	//add texture
	std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine->Get<nc::Renderer>());

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
	engine->Update();
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

	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	//if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Left) == nc::InputSystem::eKeyState::Pressed)
	//{
	//	nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
	//	//std::cout << position.x << " " << position.y << std::endl;

	//	//create particles

	//	//engine->Get<nc::ParticleSystem>()->Create(position, 20, 3, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("particle01.png", engine->Get<nc::Renderer>()), 100);
	//	//engine->Get<nc::AudioSystem>()->PlayAudio("explosion", 1, nc::RandomRange(0.2f, 2.0f));
	//	//musicChannel.SetPitch(nc::RandomRange(0.2f, 2.0f));
	//}

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();
	std::shared_ptr<nc::Texture> ka1Texture;
	std::shared_ptr<nc::Texture> operatorTexture;

	int size16 = 16;
	int size10 = 10;

	nc::Transform t1;
	nc::Transform t2;

	std::shared_ptr<nc::Font> ka1Font;
	std::shared_ptr<nc::Font> operatorFont;

	switch (state)
	{
	case Game::eState::Title:
	{
		t1.position = { 300, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f) };

		ka1Font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size16);

		ka1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		ka1Texture->Create(ka1Font->CreateSurface("Totally not Tetris", nc::Color::red));
	}

	{
		t2.position = { 350, 400 };

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		operatorTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		operatorTexture->Create(operatorFont->CreateSurface("Press TAB to Play", nc::Color::orange));
	}

		engine->Get<nc::ResourceSystem>()->Add("ka1Texture", ka1Texture);
		engine->Get<nc::ResourceSystem>()->Add("operatorTexture", operatorTexture);
		engine->Get<nc::Renderer>()->Draw(ka1Texture, t1);
		engine->Get<nc::Renderer>()->Draw(operatorTexture, t2);

		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel1:
	{
		t1.position = { 350, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f) };

		ka1Font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size16);

		ka1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		ka1Texture->Create(ka1Font->CreateSurface("Level 1", nc::Color::cyan));
	}

	{
		t2.position = { 350, 400 };

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		operatorTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		operatorTexture->Create(operatorFont->CreateSurface("Press TAB to Play", nc::Color::blue));
	}

		engine->Get<nc::ResourceSystem>()->Add("ka1Texture", ka1Texture);
		engine->Get<nc::ResourceSystem>()->Add("operatorTexture", operatorTexture);
		engine->Get<nc::Renderer>()->Draw(ka1Texture, t1);
		engine->Get<nc::Renderer>()->Draw(operatorTexture, t2);

		break;
	case Game::eState::StartLevel2:
	{
		t1.position = { 300, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f) };

		ka1Font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size16);

		ka1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		ka1Texture->Create(ka1Font->CreateSurface("Level 2", nc::Color::cyan));
	}

	{
		t2.position = { 350, 400 };

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		operatorTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		operatorTexture->Create(operatorFont->CreateSurface("Press TAB to Play", nc::Color::blue));
	}

		engine->Get<nc::ResourceSystem>()->Add("ka1Texture", ka1Texture);
		engine->Get<nc::ResourceSystem>()->Add("operatorTexture", operatorTexture);
		engine->Get<nc::Renderer>()->Draw(ka1Texture, t1);
		engine->Get<nc::Renderer>()->Draw(operatorTexture, t2);

		break;
	case Game::eState::StartLevelBoss:
	{
		t1.position = { 300, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f) };

		ka1Font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size16);

		ka1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		ka1Texture->Create(ka1Font->CreateSurface("Final Level", nc::Color::cyan));
	}

	{
		t2.position = { 350, 400 };

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		operatorTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		operatorTexture->Create(operatorFont->CreateSurface("Press TAB to Play", nc::Color::blue));
	}

		engine->Get<nc::ResourceSystem>()->Add("ka1Texture", ka1Texture);
		engine->Get<nc::ResourceSystem>()->Add("operatorTexture", operatorTexture);
		engine->Get<nc::Renderer>()->Draw(ka1Texture, t1);
		engine->Get<nc::Renderer>()->Draw(operatorTexture, t2);

		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		scene->RemoveAllActors();

		{
			t1.position = { 300, 300 + static_cast<int>(std::sin(stateTimer * 5.0f) * 15.0f) };

			ka1Font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size16);

			ka1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
			ka1Texture->Create(ka1Font->CreateSurface("Game Over", nc::Color::red));
		}

		{
			t2.position = { 350, 400 };

			operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

			operatorTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
			operatorTexture->Create(operatorFont->CreateSurface("Press TAB to Play Again", nc::Color::blue));
		}

		engine->Get<nc::ResourceSystem>()->Add("ka1Texture", ka1Texture);
		engine->Get<nc::ResourceSystem>()->Add("operatorTexture", operatorTexture);
		engine->Get<nc::Renderer>()->Draw(ka1Texture, t1);
		engine->Get<nc::Renderer>()->Draw(operatorTexture, t2);

		break;
	default:
		break;
	}

	{
		t1.position = { 30,30 };

		std::shared_ptr<nc::Texture> scoreTexture;

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		scoreTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		scoreTexture->Create(operatorFont->CreateSurface("Score: " + std::to_string(score), nc::Color::white));
	}

	{
		t2.position = { 30,40 };

		std::shared_ptr<nc::Texture> scoreTexture;

		operatorFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/8bitOperatorPlus8-Bold.ttf", &size10);

		scoreTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
		scoreTexture->Create(operatorFont->CreateSurface("Lives: " + std::to_string(lives), nc::Color::white));
	}

	engine->Draw(engine->Get<nc::Renderer>());
	scene->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt)
{
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
	{
		//stateFunction = &Game::UpdateLevelStart;
		state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt)
{
	//scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 1.0f), engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine->Get<nc::Renderer>()), 300.0f));
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

