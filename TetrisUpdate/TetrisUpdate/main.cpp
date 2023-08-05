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

void drawBlock();

void drawBlock() {
	for (int i = 0; i < 4; i++) {
		int randomNumber = rand() % 6;
		colorOfBlock[i] = randomNumber;
	}
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		shape1[i].x = (block[n][i] % 2) + 4;
		shape1[i].y = (block[n][i] / 2) - 1;
	}
}
//int countNumberOfSameBlock(Position shape);
//
//int countNumberOfSameBlock(Position shape) {
//	int count = 0;
//	if (field[shape.y][shape.x]){
//		if (field[shape.y][shape.x] == field[shape.y - 1][shape.x]) {
//			count++;
//			if (field[shape.y - 1][shape.x] == field[shape.y - 2][shape.x]) count++;
//			if (field[shape.y - 1][shape.x] == field[shape.y - 1][shape.x - 1]) count++;
//			if (field[shape.y - 1][shape.x] == field[shape.y - 1][shape.x + 1]) count++;
//		}
//		if (field[shape.y][shape.x] == field[shape.y + 1][shape.x]) {
//			count++;
//			if (field[shape.y + 1][shape.x] == field[shape.y + 2][shape.x]) count++;
//			if (field[shape.y + 1][shape.x] == field[shape.y + 1][shape.x - 1]) count++;
//			if (field[shape.y + 1][shape.x] == field[shape.y + 1][shape.x + 1]) count++;
//		}
//		if (field[shape.y][shape.x] == field[shape.y][shape.x + 1]) {
//			count++;
//			if (field[shape.y][shape.x + 1] == field[shape.y][shape.x + 2]) count++;
// 		}
//		if (field[shape.y][shape.x] == field[shape.y][shape.x - 1]) {
//			count++;
//			if (field[shape.y][shape.x - 1] == field[shape.y][shape.x - 2]) count++;
//		}
//		return count;
//	}
//}


int main(int argc, char* args[])
{
	srand(time(0));
	drawBlock();

	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return -1;
	}
	
	TTF_Font* font = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;

	SDL_Texture* textureframe = NULL;

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


	font = TTF_OpenFont("font/VT323-Regular.ttf", 90);

	SDL_Color fg = { 255, 255, 255 };

	SDL_Color bg = { 0, 0, 0 };

	string text = "GAME OVER";
	surface = TTF_RenderText_Shaded(font, text.c_str(), fg, bg);
	texture = SDL_CreateTextureFromSurface(sdlrender, surface);
	SDL_FreeSurface(surface);

	SDL_Rect srcRest;
	SDL_Rect desRect;
	SDL_Rect desRect1;
	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = 0;
	srcRest.y = 0;

	desRect.x = 337;
	desRect.y = 270;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;

	desRect1.x = 223;
	desRect1.y = 0;
	
	desRect1.w = 555;
	desRect1.h = 667;

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
			bool gameOver = false;
			int delay = 300;
			Uint32 startTime = 0;
			int countBlocks = 0;

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

				if (!gameOver) {
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
							// Delete the block out of range
							if (gameOver) {
								int topLimit = height;
								for (int i = 0; i < 4; i++) {
									if (shape2[i].y < topLimit) {
										topLimit = shape2[i].y;
									}
								}

								for (int i = 0; i < 4; i++) {
									shape2[i].y -= (shape2[i].y - topLimit);
								}
							}
							for (int i = 0; i < 4; i++) {
								field[shape2[i].y][shape2[i].x] = 1 + colorOfBlock[i];
							}
							drawBlock();
						}
						startTime = currentTime;
					}

					// Check line if have all block in this line
					int line = height - 1;
					for (int i = line; i >= 0; i--)
					{
						int count = 0;
						for (int j = 0; j < width; j++)
						{
							if (field[i][j]) {
								if (i == 0) {
									gameOver = true;
									break;
								}
								count++;
							}
							field[line][j] = field[i][j];
						}
						if (count < width) line--;
					}
				}

				delta = 0;
				isRotate = false;
				delay = 300;
				countBlocks = 0;

				SDL_RenderClear(sdlrender);

				SDL_RenderCopy(sdlrender, window.getTetrisBackground(), NULL, NULL);

				//SDL_RenderCopy(sdlrender, textureframe, NULL, &desRect1);

				// Render the tetromino when it stop
				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {
						if (field[i][j] == 0) continue;
						else {
							drawTexture(sdlrender, list_texture[field[i][j] - 1], j * SQUARE_SIZE, i * SQUARE_SIZE);
						}
					}
				}
				
				// Render the tetromino when it is running down
				for (int i = 0; i < 4; i++) {
					drawTexture(sdlrender, list_texture[colorOfBlock[i]], shape1[i].x * SQUARE_SIZE, shape1[i].y * SQUARE_SIZE);
				}

				if (gameOver == true) {
					SDL_RenderCopy(sdlrender, texture, &srcRest, &desRect);
				}

				SDL_RenderCopy(sdlrender, window.getTetrisFrame(), NULL, &desRect1);
				// Update the screen
				SDL_RenderPresent(sdlrender);
			}
		}
	}

	// Clear data
	window.cleanUp();

	return 0;
}

//int main()
//{
//	SDL_Window* window = NULL;
//	SDL_Renderer* renderer = NULL;
//	bool isRunning = true;
//	SDL_Event mainEvent;
//	TTF_Font* font = NULL;
//	SDL_Surface* surface = NULL;
//	SDL_Texture* texture = NULL;
//
//	//initializes  the subsystems
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//	{
//		printf("Unable to initialize SDL %s\n", SDL_GetError());
//		return -1;
//	}
//
//	//Initialize the truetype font API.
//	if (TTF_Init() < 0)
//	{
//		SDL_Log("%s", TTF_GetError());
//		return -1;
//	}
//
//	//Create window
//	window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
//	if (window == NULL)
//	{
//		printf("Could not create window %s", SDL_GetError());
//		return -1;
//	}
//
//	//create a renderer
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//	if (renderer == NULL)
//	{
//		printf("Could not create render %s", SDL_GetError());
//		return -1;
//	}
//
//	font = TTF_OpenFont("font/VT323-Regular.ttf", 30);
//
//	SDL_Color fg = { 243, 156, 18 };
//
//	std::string text = "Welcome you to Stdio.vn";
//	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
//	texture = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_FreeSurface(surface);
//
//	SDL_Rect srcRest;
//	SDL_Rect desRect;
//	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);
//
//	srcRest.x = 0;
//	srcRest.y = 0;
//
//	desRect.x = 200;
//	desRect.y = 270;
//
//	desRect.w = srcRest.w;
//	desRect.h = srcRest.h;
//
//	//set background color
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//	//main loop
//	while (isRunning)
//	{
//		//main event
//		while (SDL_PollEvent(&mainEvent))
//		{
//			switch (mainEvent.type)
//			{
//				//User - requested quit
//			case SDL_QUIT:
//			{
//				isRunning = false;
//				break;
//			}
//			default:
//			{
//				break;
//			}
//			}
//		}
//		// clear the window to black
//		SDL_RenderClear(renderer);
//		//Copy a portion of the texture to the current rendering target.
//		SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
//		//draw to screen
//		SDL_RenderPresent(renderer);
//	}
//	//Destroy a window.
//	SDL_DestroyWindow(window);
//	//Destroy a renderer
//	SDL_DestroyRenderer(renderer);
//	//Shutdown and cleanup the truetype font API.
//	TTF_Quit();
//	//cleans up all initialized subsystems
//	SDL_Quit();
//	return 0;
//}