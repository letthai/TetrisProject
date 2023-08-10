#ifndef BUTTON_H_
#define BUTTON_H_

#include "Header.h"
#include "handlemedia.h"

class Button
{
public:
	Button(SDL_Renderer* render, string filepath, string path, int x, int y, int w, int h);
	~Button();

	//void handleEvent(Button button, )
	void checkEventPress(SDL_Event &e);
	void drawButton(SDL_Renderer* renderer);
	bool isPressed();
	void setPressed(bool bo);
private:
	SDL_Texture* button_image;
	SDL_Texture* button_pressed;
	//SDL_Rect* rect;
	bool isSelect = false;
	bool isActive = false;// Check if the mouse go to the button
	int x, y, w, h;
};

#endif // !BUTTON_H_
