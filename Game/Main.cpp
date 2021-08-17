#include "Engine.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <cassert>

//check out GameArt.org
//nc::SeedRandom(static_cast<unsigned int>(time(nullptr))); in Game.cpp

int main(int, char**)
{
	nc::Timer timer;

	nc::Engine engine;
	engine.Startup();
	engine.Get<nc::Renderer>()->Create("GAT150", 800, 600);

	nc::Scene scene;
	scene.engine = &engine;

	nc::SetFilePath("../Resources");

	//get font
	int size = 16;
	std::shared_ptr<nc::Font> font = engine.Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/ka1.ttf", &size);

	//create font
	std::shared_ptr<nc::Texture> textTexture = std::make_shared<nc::Texture>(engine.Get<nc::Renderer>());

	//set font
	textTexture->Create(font->CreateSurface("hello wonderful world", nc::Color{ 1, 1, 1 }));

	//add font
	engine.Get<nc::ResourceSystem>()->Add("textTexture", textTexture);

	engine.Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine.Get<nc::AudioSystem>()->AddAudio("music", "audio/MarioPaint.wav");
	nc::AudioChannel channel = engine.Get<nc::AudioSystem>()->PlayAudio("music", 1, 1, true);

	std::shared_ptr<nc::Texture> texture = engine.Get<nc::ResourceSystem>()->Get<nc::Texture>("sf2.png", engine.Get<nc::Renderer>());

	for (size_t i = 0; i < 10; i++) {
		nc::Transform transform{ {nc::RandomRange(0,800),nc::RandomRange(0,600)}, nc::RandomRange(0,360), 0.25f };
		std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}

	bool quit = false;
	SDL_Event event;
	//float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		//update
		engine.Update();
		scene.Update(engine.time.deltaTime);

		if (engine.Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed)
		{
			quit = true;
		}

		if (engine.Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::Left) == nc::InputSystem::eKeyState::Pressed)
		{
			nc::Vector2 position = engine.Get<nc::InputSystem>()->GetMousePosition();
			//std::cout << position.x << " " << position.y << std::endl;

			//create particles

			engine.Get<nc::AudioSystem>()->PlayAudio("explosion", 1, nc::RandomRange(0.2f, 2.0f));
			channel.SetPitch(nc::RandomRange(0.2f, 2.0f));
		}

		//std::cout << engine.time.time << std::endl;
		//if (engine.time.time >= quitTime) quit = true;
		//engine.time.timeScale = 0.1f;

		//draw
		engine.Get<nc::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<nc::Renderer>());
		engine.Draw(engine.Get<nc::Renderer>());

		nc::Transform t;
		t.position = { 30, 30 };
		engine.Get<nc::Renderer>()->Draw(textTexture, t);

		engine.Get<nc::Renderer>()->EndFrame();
	}

	SDL_Quit();

	return 0;
}