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
#include <sstream>

#include "include\globals.h"
#include "include\functions.h"
#include "include\grid.h"
#include "include\timer.h"
#include "include\texture.h"
#include "include\clock.h"



int main( int agrc, char* args[] )
{
	if ( !Init() )
	{
		printf( "SDL failed to initialize!\n" );
	}
	else
	{
		if ( !LoadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			Grid grid;
			grid.CreateTetromino( I );

			SDL_Color textColor = { 0,0,0 };

			Timer fpsTimer;
			float averageFPS = 0;
			unsigned countedFrames = 0;

			std::stringstream fpsText;
			
			Clock clock;
			clock.Start();



			unsigned pastTicks = 0;

			fpsTimer.Start();

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
					grid.Input( e );
				}
				if ( averageFPS > 2000 )
				{
					averageFPS = 0;
				}
				

				SetRenderDrawColour( BAGE );
				SDL_RenderClear( gRenderer );

				grid.RemoveFullRow();
				
				grid.FragmentTetrominos();
				grid.ClearDeadTetrominos();

				
				
				grid.Physics( fpsTimer.GetTicks() - pastTicks );
				
				pastTicks = fpsTimer.GetTicks();

				grid.Render();
				clock.Render();

				averageFPS = countedFrames / ( fpsTimer.GetTicks() / 1000.f );
				fpsText.str( "" );
				fpsText << "" << averageFPS;
				gFPSTexture.LoadFromRenderedText( fpsText.str().c_str(), textColor );

				gFPSTexture.Render(0,0);

				SDL_RenderPresent( gRenderer );
				countedFrames++;
				
				
			}
		}
	}

	Close();

	return 0;
}
