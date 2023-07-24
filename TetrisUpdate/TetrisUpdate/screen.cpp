#include "screen.h"

//Tra ve kieu sdl surface co the tao ra image bao phu man hinh. (Load cac image)

//
////Load image vao man hinh screen
//void applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
//{
//	//tao hinh chu nhat offset
//	SDL_Rect offset;
//	offset.x = x;
//	offset.y = y;
//	SDL_BlitSurface(src, NULL, des, &offset);
//	SDL_UpdateWindowSurface(tetris_window);
//}
//



void cleanUp()
{
	//Free loaded image
	SDL_FreeSurface(tetris_background);
	tetris_background = NULL;

	//Destroy window
	SDL_DestroyWindow(tetris_window);
	tetris_window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}