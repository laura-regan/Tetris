/*
 * Project: Tetris
 * Author: Laura Isabel Regan Williams / TheLadyWithNoName
 * Date: 16-09-2017
 */

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <stdio.h>
#include <String>

#include "include\globals.h"
#include "include\functions.h"

int main( int agrc, char* args[] )
{
	if ( !Init() )
	{
		printf( "SDL failed to initialize!\n" );
	}
	else
	{
		SDL_Event e;
		bool quit = false;

		while ( !quit )
		{
			while ( SDL_PollEvent( &e ) > 0 )
			{
				if ( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			SDL_RenderClear( gRenderer );
			SDL_RenderPresent( gRenderer );
		}
	}

	Close();

	return 0;
}
