#include "Header.h"
#include "screen.h";

#undef main



//Khoi tao cac thuoc tinh ban dau, khoi tao ca font chu, audio
bool init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	else
	{
		//Create window
		tetris_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (tetris_window == NULL) return false;
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_JPG;
			if (!(IMG_Init(imgFlags) & imgFlags)) return false;
			else
			{
				//Get window surface
				tetris_screen = SDL_GetWindowSurface(tetris_window);
			}
		}
	}

	return true;
}

//tao mang chua hinh anh cac khoi

//quan ly vung choi
const int height = 20;
const int width = 10;

int field[height][width] = { 0 };

struct position {
	int x;
	int y;
}
shape1[4],
shape2[4];

int block[7][4] = {
	1, 3, 5, 7, //i
	2, 4, 5, 7, //z nguoc nam doc
	3, 5, 4, 6, //z nam doc
	3, 5, 4, 7, //t nam doc
	2, 3, 5, 7, //l bi nguoc
	3, 5, 7, 6, // j
	2, 3, 4, 5, //o vuong
};

//ve cac khoi
void draw(int n) {
	for (int i = 0; i < 4; i++) {
		shape1[i].x = block[n][i] % 2;
		shape1[i].y = block[n][i] / 2;
	}
	for (int i = 0; i < 4; i++) {
		cout << shape1[i].x << " " << shape1[i].y << endl;
	}
}

bool loadMedia()
{
	tetris_background = loadSurface("space.jpg");
	if (tetris_background == NULL) return false;
	return true;
}

SDL_Surface* loadSurface(string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, tetris_screen->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
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

				//Apply the PNG image
				SDL_BlitSurface(tetris_background, NULL, tetris_screen, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(tetris_window);
			}
		}
	}

	//Free resources and close SDL
	cleanUp();

	return 0;
}



