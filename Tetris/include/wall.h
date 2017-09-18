#ifndef WALL_H
#define WALL_H

#include <vector>

//#include "block.h"

#include "constants.h"
#include "globals.h"


enum {
	NONE,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	PURPLE,
	NUMBER_COLOURS
} COLOURS;



struct Block
{
	int colour = NONE;

	void SetColour()
	{
		switch ( colour )
		{
			case RED:
				SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF );
				break;
			case ORANGE:
				SDL_SetRenderDrawColor( gRenderer, 255, 31, 51, 0xFF );
				break;
			case YELLOW:
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 0, 0xFF );
				break;
			case GREEN:
				SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0xFF );
				break;
			case BLUE:
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 0xFF );
				break;
			case MAGENTA:
				SDL_SetRenderDrawColor( gRenderer, 255, 51, 204, 0xFF );
				break;
			case PURPLE:
				SDL_SetRenderDrawColor( gRenderer, 153, 51, 153, 0xFF );
				break;
			default:
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				break;
		}

	}

};


class Wall
{
public:
	static const int BLOCK_WIDTH = 40;
	static const int WALL_WIDTH = SCREEN_WIDTH / BLOCK_WIDTH;
	static const int WALL_HEIGHT = SCREEN_HEIGHT / BLOCK_WIDTH;

	Wall();

	void Render();

	void Physics();

	void FindEmptyRow();

	void SetBlock( int x, int j );


private:
	std::vector< std::vector<Block>> Blocks;

	void RemoveRow( int row );
};


Wall::Wall()
{
	Blocks.resize( WALL_WIDTH, std::vector<Block>( WALL_HEIGHT ) );
}


void Wall::Render()
{
	for ( int i = 0; i < WALL_WIDTH; i++ )
	{
		for ( int j = 0; j < WALL_HEIGHT; j++ )
		{
			SDL_Rect rect = { i * BLOCK_WIDTH, SCREEN_HEIGHT - (j + 1) * BLOCK_WIDTH , BLOCK_WIDTH, BLOCK_WIDTH };
			Blocks[i][j].SetColour();
			if ( Blocks[i][j].colour == NONE )
			{
				SDL_RenderDrawRect( gRenderer, &rect );
			}
			else
			{
				SDL_RenderFillRect( gRenderer, &rect );
			}

		}
	}
}


void Wall::Physics()
{
	for ( int y = 0; y < WALL_HEIGHT - 1; y++ )
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

