#ifndef HANDLE_MEDIA_H_
#define HANDLE_MEDIA_H_

#include "Header.h"

// Xu ly texture
void drawTextureBlock(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);
SDL_Texture* getTextureFromText(SDL_Renderer* render, string text, string filepath, int size, SDL_Color fg,
	SDL_Color bg, int type);

// Xu ly Surface
SDL_Surface* loadSurface(SDL_Surface* screen, string path);
void applySurface(SDL_Surface* src, SDL_Surface* des, SDL_Window* window, string filepath);

// Xu ly hinh chu nhat
void moveRect(SDL_Rect& rect, int x, int y);
SDL_Rect createRect(int x, int y, int w, int h);

// Xu ly text
void converTextToTexture(SDL_Renderer* render, string text, string filepath, int size,
								SDL_Color fg, SDL_Color bg, int type, int x1, int y1, int x2, int y2);
#endif // !HANDLE_MEDIA_H_

