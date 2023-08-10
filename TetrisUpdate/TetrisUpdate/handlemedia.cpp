#include "handlemedia.h"

void moveRect(SDL_Rect& rect, int x, int y) {
	rect.x += x;
	rect.y += y;
}

SDL_Rect createRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

void drawTextureBlock(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect destRect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	moveRect(destRect, 341, 13);
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
	SDL_Rect destRect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

SDL_Surface* loadSurface(SDL_Surface* screen, string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
				UINT32 color_key = SDL_MapRGB(optimizedSurface->format, 255, 255, 255);
				SDL_SetColorKey(optimizedSurface, SDL_TRUE, color_key);
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


//Load image vao man hinh screen
void applySurface(SDL_Surface* src, SDL_Surface* des, SDL_Window* window, string filepath)
{
	src = loadSurface(des, filepath);
	////tao hinh chu nhat offset
	//SDL_Rect offset;
	//offset.x = x;
	//offset.y = y;
	SDL_BlitSurface(src, NULL, des, NULL);
	SDL_UpdateWindowSurface(window);
}


void converTextToTexture(SDL_Renderer* render ,string text, string filepath, int size, SDL_Color fg,
								SDL_Color bg, int type, int x1, int y1, int x2, int y2) {
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font* font = TTF_OpenFont(filepath.c_str(), size);

	switch (type)
	{
	case 1:
		surface = TTF_RenderText_Shaded(font, text.c_str(), fg, bg);
	case 2:
		surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	case 3:
		surface = TTF_RenderText_Blended(font, text.c_str(), fg);
	default:
		break;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect srcRest = createRect(x1, y1, w, h);
	SDL_Rect desRect = createRect(x2, y2, w, h);

	SDL_RenderCopy(render, texture, &srcRest, &desRect);
}

SDL_Texture* getTextureFromText(SDL_Renderer* render, string text, string filepath, int size, SDL_Color fg,
	SDL_Color bg, int type) {
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font* font = TTF_OpenFont(filepath.c_str(), size);

	switch (type)
	{
	case 1:
		surface = TTF_RenderText_Shaded(font, text.c_str(), fg, bg);
	case 2:
		surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	case 3:
		surface = TTF_RenderText_Blended(font, text.c_str(), fg);
	default:
		break;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	return texture;
}