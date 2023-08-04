#ifndef HANDLE_MEDIA_H_
#define HANDLE_MEDIA_H_

#include "Header.h"

// Xu ly texture
void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void applyTexture(SDL_Renderer* renderer, SDL_Texture* texture, string filepath);
SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);

// Xu ly Surface
SDL_Surface* loadSurface(SDL_Surface* screen, string path);
void applySurface(SDL_Surface* src, SDL_Surface* des, SDL_Window* window, string filepath);

void moveRect(SDL_Rect& rect, int x, int y);
#endif // !HANDLE_MEDIA_H_

