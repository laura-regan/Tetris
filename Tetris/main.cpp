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
#include "include\wall.h"


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
		Wall wall;
		
		wall.CreateTetromino( PURPLE );
		wall.CreateTetromino( RED );

		while ( !quit )
		{
			while ( SDL_PollEvent( &e ) > 0 )
			{
				if ( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			wall.Render();
			wall.Physics();
			
			

			SDL_RenderPresent( gRenderer );
			SDL_Delay( 300 );
		}
	}

	Close();

	return 0;
}
