#include "include\functions.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "include\globals.h"
#include "include\constants.h"
#include "include\texture.h"


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

				int imgFlags = IMG_INIT_PNG;
				if ( !( IMG_Init( imgFlags ) & IMG_INIT_PNG ) )
				{
					printf( "Could not start SDL_image! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else
				{
					if ( TTF_Init() == -1 )
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


bool LoadMedia()
{
	bool success = true;

	gFont = TTF_OpenFont( "resources/fonts/OpenSans-Bold.ttf", 28 );
	if ( gFont == NULL )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		/*
		SDL_Color textColor = { 0, 0 ,0 };
		if ( !textureName.LoadFromRenderedText( "Something something" ) )
		{
			printf( "Failed to render texture!\n" );
			success = false;
		}
		*/
	}

	return success;
}


void Close()
{
	TTF_CloseFont( gFont );
	gFont = NULL;

	gFPSTexture.Free();

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
		case I: // RED
			SDL_SetRenderDrawColor( gRenderer, 228, 62, 34, 0xFF ); 
			break;
		case J: // ORANGE
			SDL_SetRenderDrawColor( gRenderer, 251, 175, 95, 0xFF );
			break;
		case O: // YELLOW
			SDL_SetRenderDrawColor( gRenderer, 250, 239, 108, 0xFF );
			break;
		case S: // GREEN
			SDL_SetRenderDrawColor( gRenderer, 161, 206, 94, 0xFF );
			break;
		case L: //BLUE
			SDL_SetRenderDrawColor( gRenderer, 26, 134, 168, 0xFF );
			break;
		case T: //MAGENTA
			SDL_SetRenderDrawColor( gRenderer, 236, 51, 140, 0xFF );
			break;
		case Z: //PURPLE
			SDL_SetRenderDrawColor( gRenderer, 152, 83, 180, 0xFF );
			break;
		case WHITE:
			SDL_SetRenderDrawColor( gRenderer, 255, 250, 255, 0xFF );
			break;
		case BLACK:
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
			break;
		case BAGE:
			SDL_SetRenderDrawColor( gRenderer, 255, 240, 200, 0xFF );
			break;
		case DARK_BAGE:
			SDL_SetRenderDrawColor( gRenderer, 255, 220, 160, 0xFF );
			break;
	}
}

void Swap( int &a, int &b )
{
	int aux = a;
	a = b;
	b = aux;
}