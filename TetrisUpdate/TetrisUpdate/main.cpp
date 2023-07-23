#include "Header.h"
#include "screen.h";

#undef main

//Khoi tao cac thuoc tinh ban dau, khoi tao ca font chu, audio
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	tetris_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE); //Kich thuoc window mac dinh la 1200, 600, 32 la chi so bit per pixel.
	if (tetris_screen == NULL) return false;
	return true;
}

int main(int arc, char* argv[]) {
	bool is_quit = false;
	if (Init() == false) return 0;

	tetris_background = LoadImage("space.jpg");
	if (tetris_background == NULL) return 0;

	applySurface(tetris_background, tetris_screen, 0, 0);

	while (!is_quit)
	{
		while (SDL_PollEvent(&tetris_event))
		{
			if (tetris_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
		}
		if (SDL_Flip(tetris_screen) == -1) return 0;
	}
	cleanUp();
	SDL_Quit();
	return 1;
}

