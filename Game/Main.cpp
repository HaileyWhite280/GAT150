#include "Game.h"

//check out GameArt.org
//TODO Do Text and Game Port and JSON
//data() json.h
//float operator [] (size_t index) const {return (&r)[index];} float& operator [] (size_t index) {return (&r)[index];}  in Color.h after r= b= c=

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