#include "window.h"

Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags) {
	tetris_window = SDL_CreateWindow(title, x, y, w, h, flags);
	tetris_renderer = SDL_CreateRenderer(tetris_window, -1, SDL_RENDERER_ACCELERATED);
	tetris_screen = SDL_GetWindowSurface(tetris_window);
}

Window::~Window() {
	// Pha huy window
	SDL_DestroyWindow(tetris_window);

	// Pha huy renderer    
	SDL_DestroyRenderer(tetris_renderer);
}

SDL_Renderer* Window::getRenderer() const {
	return tetris_renderer;
}

SDL_Window* Window::getWindow() const {
	return tetris_window;
}

SDL_Surface* Window::getTetrisScreen() const {
	return tetris_screen;
}