#ifndef SCREEN_H
#define SCREEN_H

#include "Header.h"
#include "window.h"

//Quan ly man hinh
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 667;
const int SCREEN_BPP = 32;

//Quan ly screen background va su kien
static SDL_Event tetris_event;

// Khoi tao SDL va tao cua so
bool init(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screen);

// Giai phong noi dung va dong SDL
void cleanUp();
#endif // !SCREEN_H


