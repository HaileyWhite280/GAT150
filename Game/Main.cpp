#include "Game.h"

//check out GameArt.org
//nc::SeedRandom(static_cast<unsigned int>(time(nullptr))); in Game.cpp

int main(int, char**)
{
	Game game;
	game.Initialize();

	bool quit = false;
	SDL_Event event;

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		game.Update();
		game.Draw();
	}

	SDL_Quit();

	return 0;
}