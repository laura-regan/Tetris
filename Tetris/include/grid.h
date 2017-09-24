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


std::random_device rd;
std::mt19937 mt( rd() );
std::uniform_int_distribution<int> dist( 0, 6 );

class Grid
{
public:
	int tetrominoFallSpeedStantard = 200;
	int tetrominoFallSpeed1 = 150;
	
	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics( int delta );

	void Input( SDL_Event e );

	void RemoveFullRow();

	void FragmentTetrominos();

private:
	std::vector<Tetromino > LTetromino;
	int numTetrominos;

	bool IsFreeToFall( int index );

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
			case SDLK_SPACE:
				tetrominoFallSpeed1 = 30;
				break;
		}
	}

	if ( e.type == SDL_KEYUP )
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_SPACE:
				tetrominoFallSpeed1 = 150;
				break;
		}
	}

}


void Grid::Physics( int delta )
{
	static int timePassed1 = 0;
	static int timePassed2 = 0;
	timePassed1 += delta;
	timePassed2 += delta;

	if ( timePassed1 > tetrominoFallSpeedStantard )
	{
		std::vector<bool> hasMoved;
		if ( numTetrominos >= hasMoved.capacity() )
		{
			hasMoved.resize( numTetrominos * 2 );
		}

		for ( int k = 0; k < 10; k++ )
		{
			for ( int i = 0; i < numTetrominos - 1; i++ )
			{
				if ( !hasMoved[i] )
				{
					LTetromino[i].Move( DOWN );
					if ( !IsFreeToFall( i ) )
					{
						LTetromino[i].Move( UP );
					}
					else
					{
						hasMoved[i] = true;
					}
				}
			}
		}
		hasMoved.clear();
		timePassed1 = 0;
	}

	if ( timePassed2 > tetrominoFallSpeed1 )
	{
		LTetromino[numTetrominos - 1].Move( DOWN );
		if ( !IsFreeToFall( numTetrominos - 1 ) )
		{
			LTetromino[numTetrominos - 1].Move( UP );

			int shape;
			do
			{
				shape = dist( mt );
			} while ( shape == LTetromino[numTetrominos - 1].GetShape() );
			CreateTetromino( shape );
		}

		timePassed2 = 0;
	}

}


bool Grid::IsFreeToFall( int index )
{
	if ( LTetromino[index].IsOutOfBoundsY() )
	{
		return false;
	}
	else if ( HasCollided( index ) )
	{
		return false;
	}

	return true;
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


void Grid::FragmentTetrominos()
{
	for ( int i = 0; i < numTetrominos - 1; i++ )
	{
		//try
		//{
			Tetromino* t = LTetromino[i].Fragment();
		//}
		//catch (NullptrExce )
		if ( t != NULL )
		{
			if ( LTetromino.capacity() <= numTetrominos + 1 )
			{
				LTetromino.resize( numTetrominos * 2 );
			}
			LTetromino.insert( LTetromino.end() - 1, *t );
		}
	}
}




#endif


