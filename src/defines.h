#ifndef DEFINES_H
#define DEFINES_H

#include "types.h"
#include <SDL.h>
#include <SDL_image.h>

const float ballRadius = 23;
const float cueW = 3516/3;
const float cueH = 61/3;

const int verticalScreenSize = 720;
const int horizontalScreenSize = 1280;

const float verticalTableSize = verticalScreenSize - 4 * ballRadius;
const float horizontalTableSize = horizontalScreenSize - 4 * ballRadius;

const float tableLeftBorder = 81;
const float tableRightBorder = 1198;
const float tableUpBorder = 75;
const float tableDownBorder = 643;

const Pos tableEdges[25] = {{111, 53}, {134, 75}, {601, 75}, {610, 53},
							{669, 53}, {679, 75}, {1160, 75}, {1169, 53},
							{1220, 104}, {1198, 126}, {1198, 591}, {1220, 615},
							{1169, 665}, {1160, 643}, {678, 643}, {669, 665},
							{610, 665}, {601, 643}, {133, 643}, {110, 665},
							{59, 614}, {81, 592}, {81, 127}, {59, 104},
							{111, 53}
							};

const float tableHorizontalMiddle = horizontalTableSize/2 + tableLeftBorder;
const float tableVerticalMiddle = verticalTableSize/2 + tableUpBorder;

const float frictionEffect = 0.05;
const float minVelocity = 0.1; // has to be greater than the frictionEffect.

const std::vector<Pos> startingPositions = {
	{120, tableVerticalMiddle}, //white_ball
	{700, tableVerticalMiddle}, //ball 1
	{700 + ballRadius * 2, tableVerticalMiddle + ballRadius}, //ball 2
	{700 + ballRadius * 2, tableVerticalMiddle - ballRadius}, //ball 3
	{700 + ballRadius * 4, tableVerticalMiddle + 2 * ballRadius}, //ball 4
	{700 + ballRadius * 4, tableVerticalMiddle}, //ball 5
	{700 + ballRadius * 4, tableVerticalMiddle - 2 * ballRadius}, //ball 6
	{700 + ballRadius * 6, tableVerticalMiddle + ballRadius}, //ball 7
	{700 + ballRadius * 6, tableVerticalMiddle + 3 * ballRadius}, //ball 8
	{700 + ballRadius * 6, tableVerticalMiddle - ballRadius}, //ball 9
	{700 + ballRadius * 6, tableVerticalMiddle - 3 * ballRadius}, //ball 10
	{700 + ballRadius * 8, tableVerticalMiddle}, //ball 11
	{700 + ballRadius * 8, tableVerticalMiddle + 2 * ballRadius}, //ball 12
	{700 + ballRadius * 8, tableVerticalMiddle + 4 * ballRadius}, //ball 13
	{700 + ballRadius * 8, tableVerticalMiddle - 2 * ballRadius}, //ball 14
	{700 + ballRadius * 8, tableVerticalMiddle - 4 * ballRadius}, //ball 15
};

//placeholder
const std::vector<Pos> inPositions = {
	{-10000000, 0}, 
	{-100, -100}, 
	{-1000, -1000}, 
	{-10000, -10000}, 
	{-100000, -1000000}, 
	{-1, -1000000}, 
	{-100000000, -1}, 
	{-100, -1000000}, 
	{-10000, -100}, 
	{-1000000000, -100000000000}, 
	{-100000000000, -10000000000}, 
	{-10000000000000, -100000000000000}, 
	{-100000000000, -100000000000000000}, 
	{-1000000000000000000, -100000000000000000},
	{-100000000000, -100000000000000000},
	{0, -10000000000},
};

//SDL Objects
extern SDL_Event event;
extern SDL_Window* win;
extern SDL_Renderer* rend;

extern SDL_Texture* tableTexture;
extern SDL_Texture* mainMenuTexture;
extern SDL_Texture* cueTexture;
extern SDL_Texture* triangleTexture;
extern SDL_Texture* trajectoryBallTexture;

#endif