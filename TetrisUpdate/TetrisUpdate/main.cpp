#include "Header.h"
#include "screen.h";
#include "tetris.h"
#include "window.h"
#include "handlemedia.h"
#include "media.h"

#undef main

//quan ly vung choi
const int height = 20;
const int width = 10;
const int SQUARE_SIZE = 40;

int field[height][width] = { 0 };

struct position {
	int x;
	int y;
}
shape1[4],
shape2[4];

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void draw(SDL_Renderer* renderer, SDL_Texture* texture[], int n);

//ve cac khoi
void draw(SDL_Renderer* renderer, SDL_Texture* texture[], int n) {
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < 4; i++) {
		shape1[i].x = (block[n][i] % 2) * SQUARE_SIZE + 5;
		shape1[i].y = (block[n][i] / 2) * SQUARE_SIZE + 5;
	}
	for (int i = 0; i < 4; i++) {
		int x = rand() % 6;
		drawTexture(renderer, texture[1], shape1[i].x, shape1[i].y);
	}
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect destRect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	Window window("Super Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Media media;

	SDL_Window* sdlwindow = window.getWindow();
	SDL_Renderer* sdlrender = window.getRenderer();
	SDL_Surface* sdlscreen = window.getTetrisScreen();
	SDL_Surface* sdlbackground = media.getTetrisbackground();
	SDL_Texture* sdltexture = media.getTetrisTexture();

	SDL_Texture* list_texture[] = {
		loadTexture(sdlrender, "image/block/planet_1.png"),
		loadTexture(sdlrender, "image/block/planet_2.png"),
		loadTexture(sdlrender, "image/block/planet_3.png"),
		loadTexture(sdlrender, "image/block/planet_4.png"),
		loadTexture(sdlrender, "image/block/planet_5.png"),
		loadTexture(sdlrender, "image/block/planet_6.png"), 
	};

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
				//applySurface(sdlbackground, sdlscreen, sdlwindow, "image/background/space.jpg");
				applyTexture(sdlrender, sdltexture, "image/background/space.jpg");
	draw(sdlrender, list_texture, 1);
				
				//applyTexture(sdlrender, sdltexture, "image/block/planet-1.png");
			}
		}
	}
	
	//applySurface(sdlbackground, sdlscreen, sdlwindow, "image/background/space.jpg");
	SDL_Delay(5000);
	//close SDL
	cleanUp();

	return 0;
}



