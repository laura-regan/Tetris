#include "include\functions.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "include\globals.h"
#include "include\constants.h"



bool Init()
{
	bool success = true;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Could not start SDL! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "Rainbow Tetris!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if ( gWindow == NULL )
		{
			printf( "Could not create SDL Window! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if ( gRenderer == NULL )
			{
				printf( "Could not create SDL Renderer! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

				int initFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( initFlags ) & IMG_INIT_PNG ) )
				{
					printf( "Could not start SDL_image! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else
				{
					if ( TTF_Init() != 0 )
					{
						printf( "Could not start SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError() );
						success = false;
					}
				}
			}
		}
	}

	return success;
}


void Close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}



void SetRenderDrawColour(int colour)
{
	switch ( colour )
	{
		case RED:
			SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF );
			break;
		case ORANGE:
			SDL_SetRenderDrawColor( gRenderer, 255, 31, 51, 0xFF );
			break;
		case YELLOW:
			SDL_SetRenderDrawColor( gRenderer, 255, 255, 0, 0xFF );
			break;
		case GREEN:
			SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0xFF );
			break;
		case BLUE:
			SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 0xFF );
			break;
		case MAGENTA:
			SDL_SetRenderDrawColor( gRenderer, 255, 51, 204, 0xFF );
			break;
		case PURPLE:
			SDL_SetRenderDrawColor( gRenderer, 153, 51, 153, 0xFF );
			break;
		case WHITE:
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			break;
		default:
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			break;
	}
}