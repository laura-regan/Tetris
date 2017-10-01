
#include "include\grid.h"

#include <time.h>
#include <random>

#include "timer.h"


std::random_device rd;
std::mt19937 mt( rd() );
std::uniform_int_distribution<int> dist( 0, 6 );

Grid::Grid()
{
	LTetromino.reserve( 300 );
}


void Grid::CreateTetromino( int shape )
{
	LTetromino.push_back( Tetromino( shape, GRID_COLUMNS / 2, -GRID_BUFFER ) );
}


void Grid::Render()
{
	SetRenderDrawColour( WHITE );
	SDL_RenderFillRect( gRenderer, &GRID_REC );
	SetRenderDrawColour( DARK_BAGE );
	SDL_RenderDrawRect( gRenderer, &GRID_REC );

	for ( Tetromino t : LTetromino )
	{
		t.Render();
	}
}


void Grid::Input( SDL_Event e )
{
	if ( e.type == SDL_KEYDOWN && !e.key.repeat)
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_LEFT:
				(LTetromino.end() - 1)->Move( LEFT );
				if ( ( LTetromino.end() - 1 )->IsOutOfBoundsX() )
					( LTetromino.end() - 1 )->Move( RIGHT );
				break;
			case SDLK_RIGHT:
				(LTetromino.end() - 1)->Move( RIGHT );
				if ( (LTetromino.end() - 1)->IsOutOfBoundsX() )
					(LTetromino.end() - 1)->Move( LEFT );
				break;
			case SDLK_a:
				(LTetromino.end() - 1)->Rotate( LEFT );
				if ( (LTetromino.end() - 1)->IsOutOfBoundsX() || HasCollided( ( LTetromino.size() - 1 ) ) )
					(LTetromino.end() - 1)->Rotate( RIGHT );
				break;
			case SDLK_d:
				(LTetromino.end() - 1)->Rotate( RIGHT );
				if ( (LTetromino.end() - 1)->IsOutOfBoundsX() || HasCollided( ( LTetromino.size() - 1 ) ) )
					(LTetromino.end() - 1)->Rotate( LEFT );
				break;
			case SDLK_SPACE:
				tetrominoDynamicFallSpeed = tetrominoDynamicFallSpeed2;
				break;
		}
	}

	if ( e.type == SDL_KEYUP && !e.key.repeat)
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_SPACE:
				tetrominoDynamicFallSpeed = tetrominoDynamicFallSpeed1;

				break;
		}
	}

}


void Grid::Physics( int delta )
{
	static int timePassed1;
	static int timePassed2;
	timePassed1 += delta;
	timePassed2 += delta;

	Timer timer;
	timer.Start();

	if ( timePassed1 > tetrominoStaticFallSpeed )
	{
		std::vector<bool> hasMoved;
		if ( LTetromino.size() >= hasMoved.capacity() )
		{
			hasMoved.resize( LTetromino.size() * 2);
		}

		for ( int k = 0; k < 1; k++ )
		{
			for ( int i = 0; i < LTetromino.size() - 1; i++  )
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
		timePassed1 -= tetrominoStaticFallSpeed;
	}
	
	if ( timePassed2 > tetrominoDynamicFallSpeed )
	{
		LTetromino[LTetromino.size() - 1].Move( DOWN );
		if ( !IsFreeToFall( LTetromino.size() - 1 ) )
		{
			LTetromino[LTetromino.size() - 1].Move( UP );

			int shape;
			do
			{
				shape = dist( mt );
			} while ( shape == LTetromino[LTetromino.size() - 1].GetShape() );
			CreateTetromino( shape );
		}

		timePassed2 = 0;
	}
	
	timer.Pause();
	
}


bool Grid::IsFreeToFall( int index )
{
	if ( LTetromino[index].IsOutOfBoundsY() || HasCollided( index ) )
	{
		return false;
	}
	
	return true;
}


bool Grid::HasCollided( int index )
{
	int i = 0;
	while ( i < LTetromino.size() && !LTetromino[index].IsOverlapping( LTetromino[i] ) )
	{
		i++;
		if ( i == index )
			i++;
	}

	return i < LTetromino.size() - 1;
}


void Grid::RemoveFullRow()
{
	for ( int i = GRID_ROWS + 1; i > 0; i-- )
	{
		int pointsInRow = 0;
		for ( int j = 0; j <  LTetromino.size() - 1; j++ ) // Excludes currently controlled tetromino
		{
			pointsInRow += LTetromino[j].NumPointsInRow( i );
		}

		if ( pointsInRow >= GRID_COLUMNS )
		{
			for ( int j = 0; j < LTetromino.size() - 1; j++ )
			{
				LTetromino[j].RemovePoint( i );
			}
		}
	}
}


void Grid::FragmentTetrominos()
{
	for ( int i = 0; i < LTetromino.size(); i++ )
	{
		Tetromino* t = LTetromino[i].Fragment();

		if ( t != NULL )
		{
			if ( LTetromino.size() >= LTetromino.capacity() )
			{
				LTetromino.resize( LTetromino.size() * 2 );
			}
			LTetromino.insert( LTetromino.end() - 1, *t );
		}
	}
}


void Grid::ClearDeadTetrominos()
{
	for ( it = LTetromino.begin(); it != LTetromino.end(); )
	{
		if ( it->IsEmpty() )
		{
			it = LTetromino.erase(it);
		}
		else
		{
			it++;
		}
	}
}

