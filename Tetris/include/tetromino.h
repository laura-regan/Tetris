#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

#include <vector>

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

struct Coord { int x, y; };
Coord Quads[] = { {1,1}, {-1,1}, {-1,-1}, {1,-1} };

struct Point
{
	int x, y;
	int a, b;

	void rotate()
	{
		if ( a >= 0 && b >= 0 )
		{
			a *= -1;
		}
		else if ( a <= 0 && b >= 0 )
		{
			b *= -1;
		}
		else if ( a <= 0 && b <= 0 )
		{
			a *= -1;
		}
		else if ( a >= 0 && b <= 0 )
		{
			b *= -1;
		}
	}
};

class Tetromino
{
public:
	int shape;
	static const int BLOCK_WIDTH;
	std::vector<Point> LPoint;
	SDL_Rect block;

	Tetromino( int shape, int a, int b );

	void Render();

	void Rotate();

private:

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
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[2].x = a;
			LPoint[2].y = b + 2;
			LPoint[1].a = 2;
			LPoint[1].b = 2;

			LPoint[3].x = a;
			LPoint[3].y = b + 3;
			LPoint[1].a = 3;
			LPoint[1].b = 3;
			break;
		case J:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[2].x = a - 1;
			LPoint[2].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[3].x = a - 2;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			break;
		case L:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[2].x = a + 1;
			LPoint[2].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[3].x = a + 2;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			
			break;
		case O:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[2].x = a + 1;
			LPoint[2].y = b;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[3].x = a + 1;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			
			break;
		case S:
			LPoint[1].x = a + 1;
			LPoint[1].y = b;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[2].x = a + 1;
			LPoint[2].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[3].x = a + 2;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			
			break;
		case T:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[2].x = a - 1;
			LPoint[2].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			

			LPoint[3].x = a + 1;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
			break;
		case Z:
			LPoint[1].x = a - 1;
			LPoint[1].y = b;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[2].x = a - 1;
			LPoint[2].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;

			LPoint[3].x = a - 2;
			LPoint[3].y = b + 1;
			LPoint[1].a = 1;
			LPoint[1].b = 1;
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
		block.x = LPoint[i].x;
		block.y = LPoint[i].y;

		SetRenderDrawColour( shape );
		SDL_RenderFillRect( gRenderer, &block );
		SetRenderDrawColour( shape );
		SDL_RenderDrawRect( gRenderer, &block );
	}
}


void Tetromino::Rotate()
{
	for ( int i = 1; i < LPoint.size(); i++ )
	{
		
		Swap( LPoint[i].a, LPoint[i].b );
		LPoint[i].x = LPoint[1].x + LPoint[i].a;
		LPoint[i].y = LPoint[1].y + LPoint[i].b;
	}


	switch ( shape )
	{
		case I:
			LPoint[1].x += LPoint[]
				LPoint[1].y +=
				LPoint[2].x +=
				LPoint[2].y +=
				LPoint[3].x +=
				LPoint[3].y +=
				break;
		case J:
			LPoint[1].x +=
				LPoint[1].y +=

				LPoint[2].x +=
				LPoint[2].y +=

				LPoint[3].x +=
				LPoint[3].y +=
				break;
		case L:
			LPoint[1].x +=
				LPoint[1].y +=

				LPoint[2].x +=
				LPoint[2].y +=

				LPoint[3].x +=
				LPoint[3].y +=
				break;
		case O:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[2].x = a + 1;
			LPoint[2].y = b;
			LPoint[3].x = a + 1;
			LPoint[3].y = b + 1;
			break;
		case S:
			LPoint[1].x = a + 1;
			LPoint[1].y = b;
			LPoint[2].x = a + 1;
			LPoint[2].y = b + 1;
			LPoint[3].x = a + 2;
			LPoint[3].y = b + 1;
			break;
		case T:
			LPoint[1].x = a;
			LPoint[1].y = b + 1;
			LPoint[2].x = a - 1;
			LPoint[2].y = b + 1;
			LPoint[3].x = a + 1;
			LPoint[3].y = b + 1;
			break;
		case Z:
			LPoint[1].x = a - 1;
			LPoint[1].y = b;
			LPoint[2].x = a - 1;
			LPoint[2].y = b + 1;
			LPoint[3].x = a - 2;
			LPoint[3].y = b + 1;
			break;
		default:
			printf( "Error: Unknown shape id passed." );
			break;
	}
}

#endif

