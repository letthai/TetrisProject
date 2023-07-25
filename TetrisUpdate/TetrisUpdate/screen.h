#ifndef SCREEN_H
#define SCREEN_H

#include "Header.h"

//Quan ly man hinh
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 667;
const int SCREEN_BPP = 32;

//Quan ly screen background va su kien
static SDL_Window* tetris_window = NULL;
static SDL_Surface* tetris_screen = NULL; //be mat chua boi cua so
static SDL_Surface* tetris_background = NULL; // tai anh len man hinh
static SDL_Renderer* tetris_renderer = NULL;
static SDL_Texture* tetris_texture = NULL;
static SDL_Event tetris_event;

// Khoi tao SDL va tao cua so
bool init();

// Giai phong noi dung va dong SDL
void cleanUp();

// Tai len be mat
SDL_Surface* loadSurface(string path);

// Tai len texture
SDL_Texture* loadTexture(string path);

bool loadSurfaceMedia(string path);

bool loadTextureMedia(string path);
//void applySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
#endif // !SCREEN_H


