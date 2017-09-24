#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

#include <vector>
#include <cmath>

#include "constants.h"
#include "globals.h"
#include "functions.h"




enum DIRECTIONS
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct Point
{
	int x, y;
	int a, b;

	bool operator==( Point p )
	{
		return ( x == p.x && y == p.y );
	}

	void RotateRight()
	{
		if ( a >= 0 && b >= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = abs( b );
		}
		else if ( a <= 0 && b >= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = -1 * abs( b );
		}
		else if ( a <= 0 && b <= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = -1 * abs( b );
		}
		else if ( a >= 0 && b <= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = abs( b );
		}
	}

	void RotateLeft()
	{
		if ( a >= 0 && b >= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = -1 * abs( b );
		}
		else if ( a <= 0 && b >= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = abs( b );
		}
		else if ( a <= 0 && b <= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = abs( b );
		}
		else if ( a >= 0 && b <= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = -1 * abs( b );
		}
	}
};

class Tetromino
{
public:

	/// Constructors 
	Tetromino() {};

	Tetromino( int shape, int a, int b );

	/// Rendering
	void Render();

	/// Movement
	void Rotate( DIRECTIONS dir );
	void Move( DIRECTIONS dir );

	/// Collision detection
	bool IsOverlapping( Tetromino t );
	bool IsOutOfBoundsX();
	bool IsOutOfBoundsY();

	/// Get functions
	int GetShape()
	{
		return shape;
	}


	/// Query and Modify Tetromino functions
	int NumPointsInRow( int row );
	void RemovePoint( int index );
	void Copy();
	Tetromino* Fragment();
	bool HasNeighbours( int index );


private:
	int shape;

	std::vector<Point> LPoint;
};

Tetromino::Tetromino( int shape, int a, int b )
{
	this->shape = shape;

	LPoint.resize( 4 );

	LPoint[0].x = a;
	LPoint[0].y = b;

	switch ( shape )
	{
		case I:

			LPoint[1].a = 0;
			LPoint[1].b = 1;

			LPoint[2].a = 0;
			LPoint[2].b = 2;

			LPoint[3].a = 0;
			LPoint[3].b = 3;
			break;
		case L:
			LPoint[1].a = 0;
			LPoint[1].b = -1;

			LPoint[2].a = -1;
			LPoint[2].b = 0;

			LPoint[3].a = -2;
			LPoint[3].b = 0;
			break;
		case J:
			LPoint[1].a = 0;
			LPoint[1].b = -1;

			LPoint[2].a = 1;
			LPoint[2].b = 0;

			LPoint[3].a = 2;
			LPoint[3].b = 0;
			break;
		case O:
			LPoint[1].a = 0;
			LPoint[1].b = 1;

			LPoint[2].a = 1;
			LPoint[2].b = 1;

			LPoint[3].a = 1;
			LPoint[3].b = 0;
			break;
		case S:
			LPoint[1].a = 1;
			LPoint[1].b = 0;

			LPoint[2].a = 1;
			LPoint[2].b = 1;

			LPoint[3].a = 2;
			LPoint[3].b = 1;
			break;
		case T:
			LPoint[1].a = 0;
			LPoint[1].b = -1;

			LPoint[2].a = 0;
			LPoint[2].b = 1;

			LPoint[3].a = -1;
			LPoint[3].b = 0;
			break;
		case Z:
			LPoint[1].a = 1;
			LPoint[1].b = 0;

			LPoint[2].a = 0;
			LPoint[2].b = 1;

			LPoint[3].a = -1;
			LPoint[3].b = 1;
			break;
		default:
			printf( "Error: Unknown shape id passed." );
			break;
	}
	Rotate( RIGHT );
}


void Tetromino::Render()
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		SDL_Rect block = { 0, 0, BLOCK_WIDTH, BLOCK_WIDTH };
		block.x = 0.025 * BLOCK_WIDTH + GRID_REC.x + ( LPoint[i].x + 0.05 )* BLOCK_WIDTH;
		block.y = 0.025 * BLOCK_WIDTH + GRID_REC.y + ( LPoint[i].y + 0.05 )* BLOCK_WIDTH;

		block.w *= 0.9;
		block.h *= 0.9;

		if ( LPoint[i].y >= 0 )
		{
			SetRenderDrawColour( shape );
			SDL_RenderFillRect( gRenderer, &block );
		}
	}
}


void Tetromino::Rotate( DIRECTIONS dir )
{
	for ( unsigned i = 0; i < 4; i++ )
	{
		if ( dir == LEFT )
		{
			LPoint[i].RotateLeft();
		}
		else if ( dir == RIGHT )
		{
			LPoint[i].RotateRight();
		}

		LPoint[i].x = LPoint[0].x + LPoint[i].a;
		LPoint[i].y = LPoint[0].y + LPoint[i].b;
	}
}


void Tetromino::Move( DIRECTIONS dir )
{
	switch ( dir )
	{
		case UP:
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].y--;
			break;
		case DOWN:
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].y++;
			break;
		case LEFT:
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].x--;
			break;
		case RIGHT:
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].x++;
			break;
		default:
			// Do nothing
			break;
	}
}


bool Tetromino::IsOverlapping( Tetromino t )
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		for ( int j = 0; j < t.LPoint.size(); j++ )
		{
			if ( LPoint[i] == t.LPoint[j] )
			{
				return true;
			}
		}
	}

	return false;
}


bool Tetromino::IsOutOfBoundsX()
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		if ( LPoint[i].x < 0 || LPoint[i].x  > GRID_COLUMNS - 1 )
		{
			return true;
		}
	}

	return false;
}

bool Tetromino::IsOutOfBoundsY()
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		if ( LPoint[i].y >= GRID_ROWS )
		{
			return true;
		}
	}

	return false;
}

int Tetromino::NumPointsInRow( int row )
{
	int  num = 0;
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		if ( LPoint[i].y == row )
		{
			num++;
		}
	}

	return num;
}

void Tetromino::RemovePoint( int row )
{
	int pointsRemoved = 0;

	int i = 0;
	while ( i < LPoint.size() )
	{
		if ( LPoint[i].y == row && i < LPoint.size() )
		{
			LPoint[i] = LPoint[LPoint.size() - 1];
			LPoint.pop_back();
		}
		else
		{
			i++;
		}
	}
}


Tetromino* Tetromino::Fragment()
{
	Tetromino* t = new Tetromino();

	if ( LPoint.size() > 1 && LPoint.size() < 4 )
	{
		int i = 0;
		while ( i < LPoint.size() && !HasNeighbours( i ) )
		{
			i++;
		}
		if ( i < LPoint.size() )
		{
			t->shape = this->shape;
			t->LPoint.resize( 1 );
			t->LPoint[0] = this->LPoint[i];
			printf( "f" );

			this->LPoint[i] = this->LPoint[LPoint.size() - 1];
			this->LPoint.pop_back();
		}
	}
	else
	{
		t = NULL;
	}

	return t;
}


bool Tetromino::HasNeighbours( int index )
{
	/// Neighbour is an adjacent point (Tetromino block)

	for ( int i = 0; i < LPoint.size(); i++ )
	{
		int a = LPoint[index].x - LPoint[i].x;
		int b = LPoint[index].y - LPoint[i].y;
		
		if ( a * b == 0 && abs( a + b ) == 1 )
		{
			return true;
		}
	}
	
	return false;
}



#endif

