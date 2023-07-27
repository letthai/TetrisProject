#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window
{
public:
	Window(const char* title, int x, int y, int w, int h, Uint32 flags);
	~Window();
	
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	SDL_Surface* getTetrisScreen() const;

private:
	SDL_Window* tetris_window;
	SDL_Renderer* tetris_renderer;
	SDL_Surface* tetris_screen;
};

#endif // !WINDOW_H

