#include "button.h"
#include <SDL.h>

Button::Button(SDL_Renderer* render, string filepath, string path, int x, int y, int w, int h)
{
	button_image = loadTexture(render, filepath.c_str());
	button_pressed = loadTexture(render, path.c_str());
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Button::~Button()
{
	SDL_DestroyTexture(button_image);
	SDL_DestroyTexture(button_pressed);
}

//void Button::checkEventPress(SDL_Event& e) {
//	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
//		int mouseX, mouseY;
//		SDL_GetMouseState(&mouseX, &mouseY);
//
//		bool inside = true;
//
//		if (mouseX < x || mouseX > x + w ||
//			mouseY < y || mouseY > y + h) {
//			inside = false;
//		}
//
//		if (inside) {
//			if (e.type == SDL_MOUSEMOTION) {
//				isActive = true;
//			}
//			if (e.type == SDL_MOUSEBUTTONDOWN) {
//				isSelect = true;
//			}
//			else if (e.type == SDL_MOUSEBUTTONUP) {	
//				if (isSelect) {
//					isSelect = false;
//				}
//			}
//		}
//		else isActive = false;
//	}
//}

void Button::checkEventPress(SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool inside = true;

        if (mouseX < x || mouseX > x + w ||
            mouseY < y || mouseY > y + h) {
            inside = false;
        }

        isActive = inside; // Update isActive based on whether the mouse is inside the button
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
		int mouseX1, mouseY1;
		SDL_GetMouseState(&mouseX1, &mouseY1);

		bool inside1 = true;

		if (mouseX1 < x || mouseX1 > x + w ||
			mouseY1 < y || mouseY1 > y + h) {
			inside1 = false;
		}

		if (inside1) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				isSelect = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {	
				if (isSelect) {
					isSelect = false;
				}
			}
		}
	}
}

void Button::drawButton(SDL_Renderer* render) {
	SDL_Rect rect = createRect(x, y, w, h);
	if (isActive) {
		SDL_RenderCopy(render, button_pressed, NULL, &rect);
	}
	else {
		SDL_RenderCopy(render, button_image, NULL, &rect);
	}
}

bool Button::isPressed() { return isSelect; }

void Button::setPressed(bool bo) {isSelect = bo;}