#ifndef BLOCK_H
#define BLOCK_H

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
public:
	Block(int col)
	{
		id = 0;
		colour = col;
		blockID = GetNewID();
	}

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

	

	static Block* CreateBlock( int colour )
	{
		return new Block( colour );
	}

	Block* Clone( Block* block )
	{

	}

private:
	static int id;
	int colour;
	int pieceNumber;
	int blockID;

	static int GetNewID()
	{
		return id++;
	}

};



#endif
