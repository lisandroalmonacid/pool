#ifndef DEFINES_H
#define DEFINES_H

#include "types.h"
#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const double ballRadius = 75;
const double cueW = 3516;
const double cueH = 61;
const double cueBallSpace = ballRadius / 4;

const int screenH = 1080;
const int screenW = 1920;
const SDL_Point screenOrigin = {0, 0};
const SDL_Point screenEnd = {screenW, screenH};
const SDL_Point screenMiddle = {screenW/2, screenH/2};

const double tableW = 4551;
const double tableH = 2570;
const double tableScreenW = 1200;
const double tableScreenH = tableH * tableScreenW/tableW;
const double tableScreenOffsetX = (screenW - tableScreenW) / 2;
const double tableScreenOffsetY = (screenH - tableScreenH) / 2;

const double tableLeftBorder = 293;
const double tableRightBorder = 4256;
const double tableUpBorder = 293;
const double tableDownBorder = 2277;

const Pos tableEdges[25] = {{332, 212}, {417, 293}, {2106, 293}, {2140, 212},
							{2357, 212}, {2392, 293}, {4100, 293}, {4184, 212},
							{4338, 361}, {4256, 444}, {4256, 2122}, {4338, 2207},
							{4184, 2357}, {4100, 2277}, {2392, 2277}, {2357, 2357},
							{2144, 2357}, {2110, 2276}, {420, 2277}, {336, 2357},
							{212, 2208}, {294, 2122}, {294, 443}, {211, 362}, 
							{332, 212}
							};

const double tableHorizontalMiddle = tableW/2 + tableLeftBorder;
const double tableVerticalMiddle = tableH/2 + tableUpBorder;

const double frictionEffect = 0.05;
const double minVelocity = 0.1; // has to be greater than the frictionEffect.

const std::vector<Pos> startingPositions = {
	{500, tableH/2}, //white_ball
	{tableW/2, tableH/2}, //ball 1
	{tableW/2 + ballRadius * 2, tableH/2 + ballRadius}, //ball 2
	{tableW/2 + ballRadius * 2, tableH/2 - ballRadius}, //ball 3
	{tableW/2 + ballRadius * 4, tableH/2 + 2 * ballRadius}, //ball 4
	{tableW/2 + ballRadius * 4, tableH/2}, //ball 5
	{tableW/2 + ballRadius * 4, tableH/2 - 2 * ballRadius}, //ball 6
	{tableW/2 + ballRadius * 6, tableH/2 + ballRadius}, //ball 7
	{tableW/2 + ballRadius * 6, tableH/2 + 3 * ballRadius}, //ball 8
	{tableW/2 + ballRadius * 6, tableH/2 - ballRadius}, //ball 9
	{tableW/2 + ballRadius * 6, tableH/2 - 3 * ballRadius}, //ball 10
	{tableW/2 + ballRadius * 8, tableH/2}, //ball 11
	{tableW/2 + ballRadius * 8, tableH/2 + 2 * ballRadius}, //ball 12
	{tableW/2 + ballRadius * 8, tableH/2 + 4 * ballRadius}, //ball 13
	{tableW/2 + ballRadius * 8, tableH/2 - 2 * ballRadius}, //ball 14
	{tableW/2 + ballRadius * 8, tableH/2 - 4 * ballRadius}, //ball 15
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
	{-100000000000, -100000000000000000000},
	{0, -10000000000},
};

const int msgAmount = 12;
const std::vector<std::string> messages = {
	"POOL",
	"PLAY",
	"PLAYER 1's TURN",
	"PLAYER 2's TURN",
	"PLAYER 1 HAS THE BALL IN HAND",
	"PLAYER 2 HAS THE BALL IN HAND",
	"PLAYER 1 IS SOLIDS",
	"PLAYER 2 IS SOLIDS",
	"PLAYER 1 IS STRIPES",
	"PLAYER 2 IS STRIPES",
	"PLAYER 1 WINS",
	"PLAYER 2 WINS"
};

const SDL_Color colorWhite = {255, 255, 255, 255};

extern GameState gameState;

//SDL Objects
extern SDL_Event event;
extern SDL_Window* win;
extern SDL_Renderer* rend;

extern Texture* tableTexture;
extern Texture* mainMenuTexture;
extern Texture* cueTexture;
extern Texture* triangleTexture;
extern Texture* trajectoryBallTexture;
extern Texture* ballTextures[16];
extern Texture* messageTextures[msgAmount];
extern Texture* titleTexture;
extern Texture* subtitleTexture;
#endif