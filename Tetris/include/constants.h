#ifndef CONSTANTS_H
#define CONSTANTS_H



const int RATIO_H = 4;
const int RATIO_W = 4;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = SCREEN_WIDTH * RATIO_H / RATIO_W;

static const int GRID_WIDTH = 10;
static const int GRID_HEIGHT = GRID_WIDTH * 4 / 4;
static const int GRID_BUFFER = 4;

static enum {
	NONE,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	PURPLE,
	WHITE,
	NUMBER_COLOURS
} COLOURS;


#endif