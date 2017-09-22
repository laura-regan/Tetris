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
#include "include\grid.h"
//#include "include\tetromino.h"


int main( int agrc, char* args[] )
{
	if ( !Init() )
	{
		printf( "SDL failed to initialize!\n" );
	}
	else
	{
		SDL_Event e;
		
		Grid grid;

		grid.CreateTetromino( S );
		
		unsigned currentTime = SDL_GetTicks();
		unsigned lastTime = 0;
		unsigned delta;
		unsigned physicsPeriod = 0;

		bool quit = false;
		while ( !quit )
		{
			while ( SDL_PollEvent( &e ) > 0 )
			{
				if ( e.type == SDL_QUIT )
				{
					quit = true;
				}
				grid.Input( e );
			}
			currentTime = SDL_GetTicks();
			delta = currentTime - lastTime;
			lastTime = currentTime;

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			grid.Render();
			
			//SDL_Delay( 100000 );

			physicsPeriod += delta;
			if ( physicsPeriod > 500 )
			{
				grid.Physics();
				physicsPeriod = 0;
			}

			

			if ( delta < SPF*1000 )
			{
				SDL_Delay( SPF - delta );
			}

			SDL_RenderPresent( gRenderer );
		}
	}

	Close();

	return 0;
}
