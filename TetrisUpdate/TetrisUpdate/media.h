#ifndef MEDIA_H_
#define MEDIA_H_

#include <SDL.h>

class Media
{
public:
	Media();
	~Media();

	SDL_Surface* getTetrisbackground() const;
	SDL_Texture* getTetrisTexture() const;
private:
	SDL_Surface* tetris_background;
	SDL_Texture* tetris_texture;
};
#endif // !MEDIA_H_
