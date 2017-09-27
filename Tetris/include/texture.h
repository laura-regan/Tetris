#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

#include "globals.h"

class Texture
{
public:
	Texture();

	~Texture();

	bool LoadFromRenderedText( std::string textureText, SDL_Color textColor );

	void Render(int x, int y, SDL_Rect* clip = NULL, double amgle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	void Free();

	int GetHeight();
	int GetWidth();

private:
	SDL_Texture* texture;
	int width;
	int height;

};

#endif

