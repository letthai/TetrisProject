#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "handlemedia.h"

class Window
{
public:
	Window(const char* title, int x, int y, int w, int h, Uint32 flags);
	~Window();
	
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	SDL_Surface* getTetrisScreen() const;
	SDL_Texture* getTetrisBackground() const;
	SDL_Texture* getTetrisFrame() const;
	TTF_Font* getFont() const;

	bool init();
	void cleanUp();
	SDL_Texture* createFont();

private:
	SDL_Window* tetris_window = NULL;
	SDL_Renderer* tetris_renderer = NULL;
	SDL_Surface* tetris_screen = NULL;
	SDL_Texture* tetris_background = NULL;
	SDL_Texture* tetris_frame = NULL;
	TTF_Font* font = NULL;
};

#endif // !WINDOW_H

