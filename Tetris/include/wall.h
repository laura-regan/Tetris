#ifndef WALL_H
#define WALL_H

#include <vector>

#include "block.h"

#include "constants.h"
#include "globals.h"
#include "functions.h"


class Wall
{
public:

	static const int WALL_WIDTH = 12;
	static const int WALL_HEIGHT = WALL_WIDTH * 4 / 3;
	static const int BLOCK_WIDTH = SCREEN_WIDTH / WALL_WIDTH;
	static const int WALL_BUFFER = 4;

	Wall();

	void CreateTetromino( int colour );

	void Render();

	void Physics();

	void FindEmptyRow();

	void SetBlock( int x, int j );

private:
	std::vector< std::vector<Block>> Blocks;

	Block* FBlock = new Block();

	void RemoveRow( int row );
};


Wall::Wall()
{
	Blocks.resize( WALL_WIDTH, std::vector<Block>( WALL_HEIGHT + WALL_BUFFER ) );
}




void Wall::Render()
{
	for ( int i = 0; i < WALL_WIDTH; i++ )
	{
		for ( int j = 0; j < WALL_HEIGHT; j++ )
		{
			SDL_Rect rect = { i * BLOCK_WIDTH, SCREEN_HEIGHT - ( j + 1 ) * BLOCK_WIDTH , BLOCK_WIDTH, BLOCK_WIDTH };
			if ( Blocks[i][j].colour != NONE )
			{
				SetRenderDrawColour( Blocks[i][j].colour );
				SDL_RenderFillRect( gRenderer, &rect );
				SetRenderDrawColour( NONE );
				SDL_RenderDrawRect( gRenderer, &rect );
			}
		}
	}
}


void Wall::Physics()
{
	for ( int y = 0; y < WALL_HEIGHT + WALL_BUFFER - 1; y++ )
	{
		for ( int x = 0; x < WALL_WIDTH; x++ )
		{
			if ( Blocks[x][y].colour == NONE )
			{
				Blocks[x][y] = Blocks[x][y + 1];
				Blocks[x][y + 1].colour = NONE;

			}
		}
	}
}


void Wall::FindEmptyRow()
{
	bool rowFull;

	for ( int i = 0; i < WALL_HEIGHT; i++ )
	{
		rowFull = true;

		for ( int j = 0; j < WALL_WIDTH; j++ )
		{
			if ( Blocks[j][i].colour == NONE )
			{
				rowFull = false;
			}
		}

		if ( rowFull )
		{
			RemoveRow( i );
		}
	}
}


void Wall::RemoveRow( int row )
{
	for ( int i = 0; i < WALL_WIDTH; i++ )
	{
		Blocks[i][row].colour = NONE;
	}
}


void Wall::SetBlock( int x, int y )
{
	Blocks[x][y].colour = RED;
}

#endif

