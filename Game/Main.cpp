#include "Engine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int, char**)
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("GAT150", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindowError: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::cout << nc::GetFilePath() << std::endl;
	nc::SetFilePath("../Resources");
	std::cout << nc::GetFilePath() << std::endl;

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface* surface = SDL_LoadBMP("sf2.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		//for (size_t i = 0; i < 10; i++)
		//{
		//	//get portion of image
		//	SDL_Rect src{ 32, 64, 32, 64 };
		//	//image size width & height
		//	SDL_Rect dest{ 300, 300, 64, 96 };
		//	SDL_RenderCopy(renderer, texture, &src, &dest);
		//}

		SDL_RenderPresent(renderer);
	}

	IMG_Quit();
	SDL_Quit();
	return 0;
}