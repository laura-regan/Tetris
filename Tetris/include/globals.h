#ifndef GLOBALS_H
#define GLOBALS_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

class Texture;
extern Texture gFPSTexture;




#endif
