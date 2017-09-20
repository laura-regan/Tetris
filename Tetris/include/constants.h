#ifndef CONSTANTS_H
#define CONSTANTS_H



const int RATIO_H = 4;
const int RATIO_W = 3;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = SCREEN_WIDTH * RATIO_H / RATIO_W;



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