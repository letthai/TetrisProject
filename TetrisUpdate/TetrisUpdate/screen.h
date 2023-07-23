#ifndef SCREEN_H
#define SCREEN_H

#include "Header.h"

//Quan ly man hinh
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 667;
const int SCREEN_BPP = 32;

//Quan ly screen background va su kien
static SDL_Surface* tetris_screen = NULL;
static SDL_Surface* tetris_background = NULL;
static SDL_Event tetris_event;

SDL_Surface* LoadImage(string filepath);
void applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
void cleanUp();
#endif // !SCREEN_H


