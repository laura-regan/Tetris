#ifndef BLOCK_H
#define BLOCK_H

#include "constants.h"
#include "globals.h"



class Block
{
public:
	int colour;
	int pieceNumber = 1;
	int blockID;

	Block()
	{
		//id = 0;
		colour = NONE;
		blockID = 0;
	}

	Block( int col )
	{
		//id = 0;
		colour = col;
		blockID = GetNewID();
	}

	static Block* CreateBlock( int colour )
	{
		return new Block( colour );
	}

	Block* Clone( Block* block, int type )
	{
		Block* newBlock = new Block();
		newBlock->colour = block->colour;
		newBlock->colour = type;
		newBlock->colour = block->blockID;

		return newBlock;
	}


private:
	static int id;

	static int GetNewID()
	{
		return id++;
	}
};



#endif
