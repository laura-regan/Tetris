#include "texture.h"

Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	
}


bool Texture::LoadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if ( textSurface == NULL )
	{
		printf( "Could not create texture surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if ( texture == NULL )
		{
			printf( "Failed to create texture from surface! SDL Error: %s\n", TTF_GetError() );
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface( textSurface );
	}

	return texture != NULL;

}


void Texture::Render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect quad = { x, y, width, height };

	SDL_RenderCopyEx( gRenderer, texture, clip, &quad, angle, center, flip );
}


void Texture::Free()
{
	if ( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}