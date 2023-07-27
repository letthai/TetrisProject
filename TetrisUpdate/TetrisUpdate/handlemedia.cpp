#include "handlemedia.h"

void applyTexture(SDL_Renderer* renderer, SDL_Texture* texture, string filepath) {
	texture = loadTexture(renderer, filepath);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
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

