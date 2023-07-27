#include "Header.h"
#include "screen.h";
#include "tetris.h"
#include "window.h"
#include "handlemedia.h"
#include "media.h"

#undef main

int main(int argc, char* args[])
{
	Window window("Super Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Media media;

	SDL_Window* sdlwindow = window.getWindow();
	SDL_Renderer* sdlrender = window.getRenderer();
	SDL_Surface* sdlscreen = window.getTetrisScreen();
	SDL_Surface* sdlbackground = media.getTetrisbackground();
	SDL_Texture* sdltexture = media.getTetrisTexture();

	bool flags = true;
	if (!init(window.getWindow(), window.getRenderer(), window.getTetrisScreen()))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!flags)
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				applySurface(sdlbackground, sdlscreen, sdlwindow, "image/background/space.jpg");
				//applyTexture(sdlrender, tetris_texture, "image/block/planet-1.png");
			}
		}
	}
	
	//Free resources and close SDL
	cleanUp();

	return 0;
}



