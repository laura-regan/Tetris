#ifndef GRID_H
#define GRID_H

#include <vector>

#include "block.h"

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "tetromino.h"


class Grid
{
public:

	static const int BLOCK_WIDTH = SCREEN_WIDTH / GRID_WIDTH;

	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics();

	void FindEmptyRow();

private:
	std::vector<Tetromino* > LTetromino;
	int numTetrominos;

	Tetromino* playerTetromino;

	void RemoveRow();
};

Grid::Grid()
{
	LTetromino.resize( GRID_WIDTH * ( GRID_HEIGHT + GRID_BUFFER ) / 4 * 2 );
	int numTetrominos = 0;
}


void Grid::CreateTetromino( int shape )
{
	LTetromino[numTetrominos] = new Tetromino( shape, GRID_WIDTH / 2, GRID_HEIGHT / 2);
	playerTetromino = LTetromino[numTetrominos];
	numTetrominos++;
}


void Grid::Render()
{
	for ( int i = 0; i < numTetrominos; i++ )
	{
		LTetromino[i]->Render();
	}
}


void Grid::Physics()
{
	for ( int i = 0; i < numTetrominos; i++ )
	{
		for ( int j = i + 1; j < numTetrominos; j++ )
		{

		}
	}
}


void Grid::FindEmptyRow()
{

}


void Grid::RemoveRow()
{

}



#endif


