#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

#include <vector>
#include <cmath>

#include "globals.h"
#include "functions.h"


enum
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
} SHAPES;

enum DIRECTIONS
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct Coord { int x, y; };
Coord Quads[] = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };

struct Point
{
	int x, y;
	int a, b;

	bool operator==( Point p )
	{
		return ( x == p.x && y == p.y );
	}

	void RotateLeft()
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

	void RotateRight()
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

	static const int BLOCK_WIDTH = 40;


	Tetromino( int shape, int a, int b );

	void Render();

	void Rotate( DIRECTIONS dir );

	void Move( DIRECTIONS dir );

	bool IsOverlapping( Tetromino t );

	bool IsOutOfBounds();

private:
	int shape;
	std::vector<Point> LPoint;
	SDL_Rect block;

};

Tetromino::Tetromino( int shape, int a, int b )
{
	LPoint.resize( 4 );
	block = { 0, 0, BLOCK_WIDTH, BLOCK_WIDTH };

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
		case J:
			LPoint[1].a = 0;
			LPoint[1].b = -1;

			LPoint[2].a = -1;
			LPoint[2].b = 0;

			LPoint[3].a = -2;
			LPoint[3].b = 0;
			break;
		case L:
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

}


void Tetromino::Render()
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		block.x = LPoint[i].x * BLOCK_WIDTH;
		block.y = LPoint[i].y * BLOCK_WIDTH;

		SetRenderDrawColour( 1 );
		SDL_RenderFillRect( gRenderer, &block );
		SetRenderDrawColour( 10 );
		SDL_RenderDrawRect( gRenderer, &block );
	}

	Rotate( RIGHT );
	SDL_Delay( 100 );
}


void Tetromino::Rotate( DIRECTIONS dir )
{
	for ( unsigned i = 0; i < 4; i++ )
	{
		if ( dir == RIGHT )
		{
			LPoint[i].RotateRight();
		}
		else if ( dir == LEFT )
		{
			LPoint[i].RotateLeft();
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
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].y++;
			break;
		case DOWN:
			for ( int i = 0; i < LPoint.size(); i++ ) LPoint[i].y--;
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


bool Tetromino::IsOutOfBounds()
{
	for ( int i = 0; i < LPoint.size(); i++ )
	{
		if ( LPoint[i].x < 0 || LPoint[i].x >= GRID_WIDTH ||
			 LPoint[i].y < 0 || LPoint[i].y >= GRID_HEIGHT + GRID_BUFFER )
		{
			return true;
		}
	}

	return false;
}


#endif

