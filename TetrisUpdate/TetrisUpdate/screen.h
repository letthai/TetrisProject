#ifndef SCREEN_H
#define SCREEN_H

#include "Header.h"
#include "window.h"

//Quan ly man hinh
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 667;
const int SCREEN_BPP = 32;

const int block[7][4] = {
	1, 3, 5, 7, //I
	2, 4, 5, 7, //Z nguoc nam doc
	3, 5, 4, 6, //Z nam doc
	3, 5, 4, 7, //T nam doc
	2, 3, 5, 7, //L bi nguoc
	3, 5, 7, 6, // j
	2, 3, 4, 5, //o vuong
};

// Khoi tao cac texture cho block ban dau
//SDL_Texture* list_texture(SDL_Renderer* renderer);

// Quan ly screen background va su kien
static SDL_Event tetris_event;

// Khoi tao SDL va tao cua so
bool init(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen);

// Giai phong noi dung va dong SDL
void cleanUp();
#endif // !SCREEN_H


