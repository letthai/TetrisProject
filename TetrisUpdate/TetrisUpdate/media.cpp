#include "media.h"

Media::Media()
{
	tetris_background = nullptr;
	tetris_texture = nullptr;
}

Media::~Media()
{
	SDL_FreeSurface(tetris_background);

	SDL_DestroyTexture(tetris_texture);
}

SDL_Surface* Media::getTetrisbackground() const {
	return tetris_background;
}

SDL_Texture* Media::getTetrisTexture() const {
	return tetris_texture;
}