#include "screen.h"
#include "handlemedia.h"

bool init(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

	if (window == NULL) return false;
	if (renderer == NULL) return false;
	if (screen == NULL) return false;
	//SDL_SetRenderDrawColor(window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG and JPG loading
	int imgFlags = IMG_INIT_JPG;
	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return false;
	if (!(IMG_Init(imgFlag) & imgFlag)) return false;

	return true;
}

void cleanUp()
{
	// Thoat khoi SDL
	IMG_Quit();
	SDL_Quit();
}