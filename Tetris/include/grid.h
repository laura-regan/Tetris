
#ifndef GRID_H
#define GRID_H

#include <vector>
//#include <stdlib.h>

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "tetromino.h"


class Grid
{
public:
	int tetrominoStaticFallSpeed = 70;
	
	int tetrominoDynamicFallSpeed1 = 200;
	int tetrominoDynamicFallSpeed2 = 30;
	int tetrominoDynamicFallSpeed = 200;

	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics( int delta );

	void Input( SDL_Event e );

	void RemoveFullRow();

	void FragmentTetrominos();

	void ClearDeadTetrominos();

private:
	std::vector<Tetromino > LTetromino;
	std::vector<Tetromino>::iterator it;
	

	bool IsFreeToFall( int index );

	bool HasCollided( int index );
};



#endif


