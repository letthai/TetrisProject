#include "window.h"

Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags) {
	tetris_window = SDL_CreateWindow(title, x, y, w, h, flags);
	tetris_renderer = SDL_CreateRenderer(tetris_window, -1, SDL_RENDERER_ACCELERATED);
	tetris_screen = SDL_GetWindowSurface(tetris_window);
	tetris_frame = loadTexture(tetris_renderer, "image/frame/frame.png");
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

SDL_Texture* Window::getTetrisBackground() const {
	return tetris_background;
}

SDL_Texture* Window::getTetrisFrame() const {
	return tetris_frame;
}

SDL_Texture* Window::getTable() const {
	return table;
}

Mix_Chunk* Window::getSound() const {
	return sound;
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	if (TTF_Init() < 0) return false;

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	sound = Mix_LoadWAV("sound/sound.wav");

	if (tetris_window == NULL) return false;
	if (tetris_renderer == NULL) return false;
	if (tetris_screen == NULL) return false;

	//Initialize PNG and JPG loading
	int imgFlags = IMG_INIT_JPG;
	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return false;
	if (!(IMG_Init(imgFlag) & imgFlag)) return false;

	SDL_Surface* sdlbackground = loadSurface(tetris_screen, "image/background/space1.png");
	tetris_background = SDL_CreateTextureFromSurface(tetris_renderer, sdlbackground);

	SDL_Surface* sdltable = loadSurface(tetris_screen, "image/background/table.png");
	table = SDL_CreateTextureFromSurface(tetris_renderer, sdltable);
	return true;
}


void Window::cleanUp() {
	// Thoat khoi SDL
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}