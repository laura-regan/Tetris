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


struct Point
{
	int x;
	int y;
};

class Tetromino
{
public:
	int shape;
	static const int BLOCK_WIDTH;
	std::vector<Point> LPoint;
	SDL_Rect block;

	Tetromino( int shape );

	void Render();

private:

};

Tetromino::Tetromino( int shape )
{
	LPoint.resize( 4 );
	block = { 0, 0, BLOCK_WIDTH, BLOCK_WIDTH };

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


#endif

