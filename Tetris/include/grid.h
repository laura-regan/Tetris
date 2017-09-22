#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "block.h"

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "tetromino.h"


class Grid
{
public:

	static const int BLOCK_WIDTH = SCREEN_WIDTH / GRID_WIDTH;

	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics();



	void Input( SDL_Event e );

	void FindEmptyRow();

private:
	std::vector<Tetromino > LTetromino;
	int numTetrominos;

	Tetromino* playerTetromino;

	void RemoveRow();

	bool HasCollided( int index );
};

Grid::Grid()
{
	LTetromino.resize(GRID_WIDTH * GRID_HEIGHT * 2);
	int numTetrominos = 0;
}


void Grid::CreateTetromino( int shape )
{
	LTetromino[numTetrominos] = Tetromino( shape, GRID_WIDTH / 2, 4 );
	numTetrominos++;
	printf( "f" );
}


void Grid::Render()
{
	for ( int i = 0; i < numTetrominos; i++ )
	{
		LTetromino[i].Render();
	}
}


void Grid::Input( SDL_Event e )
{
	if ( e.type == SDL_KEYDOWN )
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_LEFT:
				LTetromino[numTetrominos - 1].Move( LEFT );
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() )
					LTetromino[numTetrominos - 1].Move( RIGHT );
				break;
			case SDLK_RIGHT:
				LTetromino[numTetrominos - 1].Move( RIGHT );
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() )
					LTetromino[numTetrominos - 1].Move( LEFT );
				break;
			case SDLK_a:
				LTetromino[numTetrominos - 1].Rotate( LEFT );
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() )
					LTetromino[numTetrominos - 1].Rotate( RIGHT );
				break;
			case SDLK_d:
				LTetromino[numTetrominos - 1].Rotate( RIGHT );
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() )
					LTetromino[numTetrominos - 1].Rotate( LEFT );
				break;
		}
	}
}


void Grid::Physics()
{
	std::vector<bool> hasMoved( 10 );
	
	for ( int i = 0; i < numTetrominos; i++ )
	{
		
		if ( !hasMoved[i] )
		{
			LTetromino[i].Move( DOWN );
			if ( LTetromino[i].IsOutOfBoundsY() )
			{
				LTetromino[i].Move( UP );
				if ( i == numTetrominos - 1 )
				{
					srand( time( NULL ) );
					CreateTetromino( rand() % 6 );
				}
			}
			else if ( HasCollided( i ) )
			{
				LTetromino[i].Move( UP );
				if ( i == numTetrominos - 1 )
				{
					srand( time( NULL ) );
					CreateTetromino( rand() % 6 );
				}
			}
			else
			{
				hasMoved[i] = true;
			}
		}
	}
}


bool Grid::HasCollided( int index )
{
	int i = 0;
	while ( i < numTetrominos && !LTetromino[index].IsOverlapping( LTetromino[i] ) )
	{
		i++;
		if ( i == index )
			i++;
	}

	return i < numTetrominos - 1;
}


void Grid::FindEmptyRow()
{

}


void Grid::RemoveRow()
{

}



#endif


