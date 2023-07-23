#include "screen.h"

//Tra ve kieu sdl surface co the tao ra image bao phu man hinh. (Load cac image)
SDL_Surface* LoadImage(string filepath) {
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;

	load_image = IMG_Load(filepath.c_str());
	if (load_image != NULL) {
		//Toi uu hoa anh cho phu hop cua so
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}

	return optimize_image;
}

//Load image vao man hinh screen
void applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	//tao hinh chu nhat offset
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

void cleanUp()
{
	SDL_FreeSurface(tetris_screen);
	SDL_FreeSurface(tetris_background);
}