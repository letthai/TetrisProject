#include "Header.h"
#include "window.h"
#include "handlemedia.h"

#undef main

// Create array to check if this location has block
int field[height][width] = { 0 };

int colorOfBlock[4];

struct Position {
	int x;
	int y;
}
shape1[4],
shape2[4];

// Check the tetromino inside the play zone or not?
bool check() {
	for (int i = 0; i < 4; i++) {
		if (shape1[i].x < 0 || shape1[i].x >= width || shape1[i].y >= height) return false;
		else if (field[shape1[i].y][shape1[i].x]) return false;
	}
	return true;
}

int main(int argc, char* args[])
{
	srand(time(0));

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
			int score = 0;
			SDL_Event e;
			int delta = 0;
			bool isRotate = false;
			int delay = 300;
			Uint32 startTime = 0;
			//While application is running
			while (isPlaying)
			{

				Uint32 currentTime = SDL_GetTicks();

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
							delay = 50;
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

				// Move tetromino to the left or right
				for (int i = 0; i < 4; i++) {
					shape2[i] = shape1[i];
					shape1[i].x += delta;
				}
				if (!check()) {
					for (int i = 0; i < 4; i++) shape1[i] = shape2[i];
				}

				// Rotate the tetromino
				if (isRotate) {
					Position point = shape1[1];
					for (int i = 0; i < 4; i++) {
						int a = shape1[i].y - point.y;
						int b = shape1[i].x - point.x;
						shape1[i].x = point.x - a;
						shape1[i].y = point.y + b;
					}
					if (!check()) for (int i = 0; i < 4; i++) shape1[i] = shape2[i];
				}

				// Run down the tetromino faster and create new tetromino
				if (currentTime - startTime > delay) {
					for (int i = 0; i < 4; i++) {
						shape2[i] = shape1[i];
						shape1[i].y++;
					}
					if (!check()) {
						for (int i = 0; i < 4; i++) {
							field[shape2[i].y][shape2[i].x] = 1 + colorOfBlock[i];
						}
						for (int i = 0; i < 4; i++) {
							int randomNumber = rand() % 6;
							colorOfBlock[i] = randomNumber;
						}
						int n = rand() % 7;
						for (int i = 0; i < 4; i++) {
							shape1[i].x = (block[n][i] % 2);
							shape1[i].y = (block[n][i] / 2);
						}
					}
					startTime = currentTime;
				}

				// Check line if have all block in this line
				int line = height - 1;
				for (int i = height - 1; i > 0; i--)
				{
					int count = 0;
					for (int j = 0; j < width; j++)
					{
						if (field[i][j]) count++;
						field[line][j] = field[i][j];
					}
					if (count < width) line--;
				}

				// Check group of the block if have same texture
				/*int count = 0;
				for (int i = 0; i < 4; i++) {
					if()
				}*/

				delta = 0;
				isRotate = false;
				delay = 300;

				SDL_RenderClear(sdlrender);

				SDL_RenderCopy(sdlrender, window.getTetrisBackground(), NULL, NULL);

				// Render the tetromino when it stop
				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {
						if (field[i][j]) {
							drawTexture(sdlrender, list_texture[field[i][j] - 1], j * SQUARE_SIZE, i * SQUARE_SIZE);
						}
					}
				}

				// Render the tetromino when it is running down
				for (int i = 0; i < 4; i++) {
					drawTexture(sdlrender, list_texture[colorOfBlock[i]], shape1[i].x * SQUARE_SIZE, shape1[i].y * SQUARE_SIZE);
				}

				// Update the screen
				SDL_RenderPresent(sdlrender);
			}
		}
	}

	// Clear data
	window.cleanUp();

	return 0;
}