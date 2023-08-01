#include "Header.h"
#include "window.h"
#include "handlemedia.h"

#undef main

//quan ly vung choi
const int height = 20;
const int width = 10;
const int SQUARE_SIZE = 32;

int field[height][width] = { 0 };

struct Position {
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
	if (shape1[0].x == 0) {
		for (int i = 0; i < 4; i++) {
				shape1[i].x = (block[n][i] % 2);
				shape1[i].y = (block[n][i] / 2);
			}
	}
	
	for (int i = 0; i < 4; i++) {
		int x = rand() % 6;
		drawTexture(renderer, texture[x], shape1[i].x * SQUARE_SIZE, shape1[i].y * SQUARE_SIZE);
	}
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect destRect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

int main(int argc, char* args[])
{
	Window window("Super Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* sdlrender = window.getRenderer();

	SDL_Texture* list_texture[] = {
		loadTexture(sdlrender, "image/block/planet_1.png"),
		loadTexture(sdlrender, "image/block/planet_2.png"),
		loadTexture(sdlrender, "image/block/planet_3.png"),
		loadTexture(sdlrender, "image/block/planet_4.png"),
		loadTexture(sdlrender, "image/block/planet_5.png"),
		loadTexture(sdlrender, "image/block/planet_6.png"), 
	};

	bool flags = true;
	if (!window.init())
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
			bool isPlaying = true;
			SDL_Event e;
			int delta = 0;
			bool isRotate = false;
			//While application is running
			while (isPlaying)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:
						isPlaying = false;
					case SDL_KEYDOWN:
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							isRotate = true;
							break;
						case SDLK_DOWN:
							break;
						case SDLK_LEFT:
							delta = -1;
							break;
						case SDLK_RIGHT:
							delta = 1;
							break;
						default:
							break;
						}
					default:
						break;
					}
				}

				for (int i = 0; i < 4; i++) {
					shape1[i].x += delta;
				}

				if (isRotate) {
					Position point = shape1[2];
					for (int i = 0; i < 4; i++) {
						int a = shape1[i].y - point.y;
						int b = shape1[i].x - point.x;
						shape1[i].x = point.x - a;
						shape1[i].y = point.y + b;
 					}
				}

				SDL_SetRenderDrawColor(sdlrender, 0, 0, 0, 255);
				SDL_RenderClear(sdlrender);

				// Draw background
				SDL_RenderCopy(sdlrender, window.getTetrisBackground(), NULL, NULL);

				// Draw the tetromino
				draw(sdlrender, list_texture, 1);

				// Reset the variable of action
				delta = 0;
				isRotate = false;

				// Update the screen
				SDL_RenderPresent(sdlrender);
			}
		}
	}
	
	window.cleanUp();

	return 0;
}



