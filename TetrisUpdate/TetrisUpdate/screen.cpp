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

//bool loadSurfaceMedia(string path)
//{
//	tetris_background = loadSurface(path.c_str());
//	if (tetris_background == NULL) return false;
//	return true;
//}
//
//bool loadTextureMedia(string path)
//{
//	tetris_texture = loadTexture(path.c_str());
//	if (tetris_texture == NULL) return false;
//	return true;
//}

void cleanUp()
{
	// Giai phong be mat
	SDL_FreeSurface(tetris_background);
	tetris_background = NULL;

	// Pha huy cua so
	SDL_DestroyWindow(tetris_window);
	tetris_window = NULL;

	// Giai phong texture
	SDL_DestroyTexture(tetris_texture);
	tetris_texture = NULL;

	// Pha huy renderer    
	SDL_DestroyRenderer(tetris_renderer);
	tetris_renderer = NULL;

	// Thoat khoi SDL
	IMG_Quit();
	SDL_Quit();
}