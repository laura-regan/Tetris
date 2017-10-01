#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

/// Frames-per-Second and Seconds-per-Frame
const int FPS = 60;
const double SPF = 1 / FPS;

/// Window Aspect Ratio
const int RATIO_H = 16;
const int RATIO_W = 9;

/// Window Dimensions
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = SCREEN_WIDTH * RATIO_H / RATIO_W;

const int GRID_COLUMNS = 13;
const int GRID_ROWS = 26;

const int LOWER_BORDER = SCREEN_HEIGHT * 0.1;
const int UPPER_BORDER = SCREEN_HEIGHT * 0.02;

const int GRID_HEIGHT = SCREEN_HEIGHT - LOWER_BORDER - UPPER_BORDER;

const int BLOCK_WIDTH = GRID_HEIGHT / GRID_ROWS;

const int GRID_WIDTH = BLOCK_WIDTH * GRID_COLUMNS;

const int SIDE_BORDER = ( SCREEN_WIDTH - GRID_WIDTH ) / 2;

static const int GRID_BUFFER = 4;

static const SDL_Rect GRID_REC = { SIDE_BORDER, UPPER_BORDER, GRID_WIDTH, GRID_HEIGHT };

static enum COLOUR
{
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	PURPLE,
	WHITE,
	BLACK,
	BAGE,
	DARK_BAGE,
	NUMBER_COLOURS
};

static enum SHAPE
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};


#endif