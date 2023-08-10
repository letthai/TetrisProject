#include "Header.h"
#include "window.h"
#include "handlemedia.h"
#include "button.h"

#undef main

// Create array to check if this location has block
int field[height][width] = { 0 };

struct Position {
	int x;
	int y;
}
shape1[4],
shape2[4];

int colorOfBlock[4];

const string saveFilename = "save_game.bin";

struct GameState {
	int field_save[height][width];
	int colorOfBlock_save[4];
	Position shape1_save[4];
	Position shape2_save[4];
	int level_save;
	int score_save;
}gameState;

void SaveGame(const GameState& gameState, string filename) {
	// Open the file for binary write
	std::ofstream outFile(filename.c_str(), std::ios::binary);
	if (outFile.is_open()) {
		// Write the game state struct to the file
		outFile.write(reinterpret_cast<const char*>(&gameState), sizeof(gameState));
		outFile.close();
		cout << "save ok";
	}
	else {
		std::cerr << "Failed to open file for writing." << std::endl;
	}
}

// Function to load the game state from a file
void LoadGame(GameState& gameState, string filename) {
	// Open the file for binary read
	std::ifstream inFile(filename.c_str(), std::ios::binary);
	if (inFile.is_open()) {
		// Read the game state struct from the file
		inFile.read(reinterpret_cast<char*>(&gameState), sizeof(gameState));
		inFile.close();
		cout << "load ok";
	}
	else {
		std::cerr << "Failed to open file for reading." << std::endl;
	}
}

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

	Button button_start(sdlrender, "image/button/play_1.png", "image/button/play_2.png", 426, 175, 150, 70);
	Button button_continue(sdlrender, "image/button/continue_1.png", "image/button/continue_2.png", 426, 265, 150, 70);
	Button button_quit(sdlrender, "image/button/quit_1.png", "image/button/quit_2.png", 426, 445, 150, 70);
	Button button_retry(sdlrender, "image/button/retry_1.png", "image/button/retry.png", 50, 124, 40, 40);
	Button button_mainsc(sdlrender, "image/button/x_1.png", "image/button/x_2.png", 115, 124, 40, 40);
	Button button_pause(sdlrender, "image/button/pause_1.png", "image/button/pause_2.png", 900, 10, 40, 40);
	Button button_hs(sdlrender, "image/button/hs_1.png", "image/button/hs_2.png", 426, 355, 150, 70);
	Button button_resume(sdlrender, "image/button/resume_1.png", "image/button/resume_2.png", 426, 175, 150, 70);
	Button button_save(sdlrender, "image/button/save_1.png", "image/button/save_2.png", 426, 265, 150, 70);
	Button button_mute(sdlrender, "image/button/mute.png", "image/button/mute.png", 950, 10, 40, 40);
	Button button_unmute(sdlrender, "image/button/unmute_1.png", "image/button/unmute_1.png", 950, 10, 40, 40);
	Button button_x(sdlrender, "image/button/x_1.png", "image/button/x_2.png", 680, 235, 50, 50);

	int hi = 0;
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
			// Khai bao cac bien
			bool isPlaying = true;
			bool isStarted = false;
			int score = 0;
			SDL_Event e;
			int delta = 0;
			bool isRotate = false;
			bool gameOver = false;
			int delay = 300;
			Uint32 startTime = 0;
			int countBlocks = 0;
			bool isPause = false;
			bool isSave = false;
			int level = 0;
			bool isContinue = false;
			bool playSound = true;
			bool isCheckHs = false;

			SDL_Color fg = { 255, 255, 255 };
			SDL_Color bg = { 0, 0, 0 };

			// Render background
			SDL_RenderCopy(sdlrender, window.getTetrisBackground(), NULL, NULL);
			//While application is running
			while (isPlaying)
			{
				// Play sound
				Mix_PlayChannel(-1, window.getSound(), 0);

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
					case SDL_MOUSEBUTTONDOWN:
						button_start.checkEventPress(e);
						button_continue.checkEventPress(e);
						button_quit.checkEventPress(e);
						button_retry.checkEventPress(e); 
						button_mainsc.checkEventPress(e);
						button_pause.checkEventPress(e); 
						button_resume.checkEventPress(e);
						button_save.checkEventPress(e);
						button_mute.checkEventPress(e);
						button_unmute.checkEventPress(e);
						button_hs.checkEventPress(e);
						button_x.checkEventPress(e);
						if (button_quit.isPressed() == true) isPlaying = false;

						if (button_hs.isPressed() == true) isCheckHs = true;
						else if (button_x.isPressed() == true) isCheckHs = false;

						if (button_unmute.isPressed() == true && playSound == true) playSound = false;
						else if (button_mute.isPressed() == true) {
							if (playSound == false) playSound = true;
						}

						// Check pause or resume game
						if (button_pause.isPressed() == true && isPause == false) isPause = true;
						else if (button_resume.isPressed() == true) {
							if (isPause == true) isPause = false;
						}

						// Check if user save game
						if (button_save.isPressed() == true) {
							isSave = true;

							if (isSave == true) {
								for (int i = 0; i < height; i++) {
									for (int j = 0; j < width; j++) {
										gameState.field_save[i][j] = field[i][j];
									}
								}
								for (int i = 0; i < 4; i++) {
									gameState.shape1_save[i].x = shape1[i].x;
									gameState.shape1_save[i].y = shape1[i].y;
									gameState.shape2_save[i].x = shape2[i].x;
									gameState.shape2_save[i].y = shape2[i].y;
									gameState.colorOfBlock_save[i] = colorOfBlock[i];
								}
								gameState.score_save = score;
								gameState.level_save = level;
							}
							SaveGame(gameState, saveFilename);
							break;
						}

						// Check if user load save game
						if (button_continue.isPressed() == true) {
							isContinue = true;
							if (isContinue == true) {
								LoadGame(gameState, saveFilename);
								isStarted = true; // Bắt đầu trò chơi
							}

						}

						// Check if user start game
						if (button_start.isPressed() == true && isStarted == false) {
							isStarted = true;
						}
						else if (gameOver == true) {
							// Retry game
							if (button_retry.isPressed() == true) {
								gameOver = false;
								isStarted = true;
								score = 0;
								memset(field, 0, sizeof(field));
								drawBlock();
							}
							// Back to main screen
							else if (button_mainsc.isPressed() == true) {
								gameOver = false;
								isStarted = false;
								score = 0;
								memset(field, 0, sizeof(field));
								drawBlock();
							}
						}
					case SDL_MOUSEBUTTONUP:
						button_start.checkEventPress(e);
						button_continue.checkEventPress(e);
						button_quit.checkEventPress(e);
						button_retry.checkEventPress(e);
						button_mainsc.checkEventPress(e);
						button_pause.checkEventPress(e);
						button_resume.checkEventPress(e);
						button_save.checkEventPress(e);
						button_mute.checkEventPress(e);
						button_unmute.checkEventPress(e);
						button_hs.checkEventPress(e);
						button_x.checkEventPress(e);
					case SDL_MOUSEMOTION:
						button_start.checkEventPress(e);
						button_continue.checkEventPress(e);
						button_quit.checkEventPress(e);
						button_retry.checkEventPress(e);
						button_mainsc.checkEventPress(e);
						button_pause.checkEventPress(e);
						button_resume.checkEventPress(e);
						button_save.checkEventPress(e);
						button_mute.checkEventPress(e);
						button_unmute.checkEventPress(e);
						button_hs.checkEventPress(e);
						button_x.checkEventPress(e);
					default:
						break;
					}
				}

				SDL_RenderClear(sdlrender);

				// Render background
				SDL_RenderCopy(sdlrender, window.getTetrisBackground(), NULL, NULL);

				// Set volume when click button mute or unmute
				if (playSound == true) {
					button_unmute.drawButton(sdlrender);
					Mix_VolumeChunk(window.getSound(), 10);
				}
				else {
					button_mute.drawButton(sdlrender);
					Mix_VolumeChunk(window.getSound(), 0);
				}

				//Render frame
				SDL_Rect desRect1 = createRect(223, 0, 555, 667);
				SDL_RenderCopy(sdlrender, window.getTetrisFrame(), NULL, &desRect1);
				
				if (isStarted == false) {
					if (isCheckHs == false) {
						button_start.drawButton(sdlrender);
						button_continue.drawButton(sdlrender);
						button_hs.drawButton(sdlrender);
						button_quit.drawButton(sdlrender);
					}
					else {
						// Render High Score
						SDL_Rect desRect2 = createRect(300, 260, 350, 150);
						SDL_Texture* texture_hs = getTextureFromText(sdlrender, to_string(hi), "font/VT323-Regular.ttf", 65, fg, bg, 1);
						int centeredTextureWidth, centeredTextureHeight;
						SDL_QueryTexture(texture_hs, NULL, NULL, &centeredTextureWidth, &centeredTextureHeight);

						SDL_Rect destinationRect;
						destinationRect.x = 300 + (400 - centeredTextureWidth) / 2;
						destinationRect.y = 260 + (150 - centeredTextureHeight) / 2;
						destinationRect.w = centeredTextureWidth;
						destinationRect.h = centeredTextureHeight;

						SDL_RenderCopy(sdlrender, window.getTable(), NULL, &desRect2);
						button_x.drawButton(sdlrender);
						SDL_RenderCopy(sdlrender, texture_hs, NULL, &destinationRect);
					}
				}
				else {
					if (!gameOver) {
						if (isPause == false) button_pause.drawButton(sdlrender);
						
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
						if(isPause == false) {
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
							else {
								score += 100;
							}
						}
					}

					delta = 0;
					isRotate = false;
					delay = 300;
					countBlocks = 0;

					// Render the tetromino when it stop
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							if (field[i][j] == 0) continue;
							else {
								drawTextureBlock(sdlrender, list_texture[field[i][j] - 1], j * SQUARE_SIZE, i * SQUARE_SIZE);
							}
						}
					}

					// Render the tetromino when it is running down
					for (int i = 0; i < 4; i++) {
						drawTextureBlock(sdlrender, list_texture[colorOfBlock[i]], shape1[i].x * SQUARE_SIZE, shape1[i].y * SQUARE_SIZE);
					}

					if (isPause == true) {
						button_resume.drawButton(sdlrender);
						button_save.drawButton(sdlrender);
						button_quit.drawButton(sdlrender);

					}

					if (gameOver == true) {
						if (score >= hi) hi = score;
						converTextToTexture(sdlrender, "Retry?", "font/VT323-Regular.ttf", 50, fg, bg, 1, 0, 0, 50, 70);
						button_retry.drawButton(sdlrender);
						button_mainsc.drawButton(sdlrender);
						converTextToTexture(sdlrender, "GAME OVER", "font/VT323-Regular.ttf", 90, fg, bg, 1, 0, 0, 337, 270);
					}

					converTextToTexture(sdlrender, to_string(score), "font/VT323-Regular.ttf", 65, fg, bg, 1, 0, 0, 765, 115);
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