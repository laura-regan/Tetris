#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "block.h"

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "tetromino.h"


std::default_random_engine rng;
std::uniform_int_distribution<int> dist( 0, 6 );

class Grid
{
public:

	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics( int delta );

	void Input( SDL_Event e );

	void RemoveFullRow();

private:
	std::vector<Tetromino > LTetromino;
	int numTetrominos;

	bool HasCollided( int index );
};

Grid::Grid()
{
	LTetromino.resize( GRID_WIDTH * GRID_HEIGHT * 2 );
	int numTetrominos = 0;
}


void Grid::CreateTetromino( int shape )
{
	LTetromino[numTetrominos] = Tetromino( shape, GRID_COLUMNS / 2, -GRID_BUFFER );
	numTetrominos++;
}


void Grid::Render()
{
	SetRenderDrawColour( WHITE );
	SDL_RenderFillRect( gRenderer, &GRID_REC );
	SetRenderDrawColour( DARK_BAGE );
	SDL_RenderDrawRect( gRenderer, &GRID_REC );

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
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() || HasCollided( numTetrominos - 1 ) )
					LTetromino[numTetrominos - 1].Rotate( RIGHT );
				break;
			case SDLK_d:
				LTetromino[numTetrominos - 1].Rotate( RIGHT );
				if ( LTetromino[numTetrominos - 1].IsOutOfBoundsX() || HasCollided( numTetrominos - 1 ) )
					LTetromino[numTetrominos - 1].Rotate( LEFT );
				break;
		}
	}
}


void Grid::Physics( int delta )
{
	static int timePassed = 0;
	timePassed += delta;

	if ( timePassed > 200 )
	{
		std::vector<bool> hasMoved;
		if ( numTetrominos >= hasMoved.capacity() )
		{
			hasMoved.resize( numTetrominos * 2 );
		}

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
						int shape;
						do
						{
							shape = dist( rng );
						} while ( shape == LTetromino[numTetrominos - 1].GetShape() );
						CreateTetromino( shape );
					}
				}
				else if ( HasCollided( i ) )
				{
					LTetromino[i].Move( UP );
					if ( i == numTetrominos - 1 )
					{
						int shape;
						do
						{
							shape = dist( rng );
						} while ( shape == LTetromino[numTetrominos - 1].GetShape() );
						CreateTetromino( shape );
					}
				}
				else
				{
					hasMoved[i] = true;
				}
			}
		}

		hasMoved.clear();
		timePassed = 0;
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


void Grid::RemoveFullRow()
{
	for ( int i = GRID_ROWS + 1; i > 0; i-- )
	{
		int pointsInRow = 0;
		for ( int j = 0; j < numTetrominos - 1; j++ ) // Excludes currently controlled tetromino
		{
			pointsInRow += LTetromino[j].NumPointsInRow( i );
		}

		if ( pointsInRow >= GRID_COLUMNS )
		{
			for ( int j = 0; j < numTetrominos - 1; j++ )
			{
				LTetromino[j].RemovePoint( i );
			}
		}
	}
}






#endif


