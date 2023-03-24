#ifndef DEFINES_H
#define DEFINES_H

#include "types.h"
const float pi = 3.141592;
const float ballRadius = 20;

//la posición central de la mesa es 0, 0
//limite izquierdo = -h_table_radius
//limite derecho = h_table_radius
//limite superior = v_table_radius
//limite inferior = -v_table_radius

const int verticalScreenSize = 720;
const int horizontalScreenSize = 1280;

const float verticalTableSize = verticalScreenSize - 4 * ballRadius;
const float horizontalTableSize = horizontalScreenSize - 4 * ballRadius;

const float tableLeftBorder = ballRadius * 2;
const float tableRightBorder = horizontalScreenSize - ballRadius * 2;
const float tableUpBorder = ballRadius * 2;
const float tableDownBorder = verticalScreenSize - 2 * ballRadius;

const float tableHorizontalMiddle = horizontalTableSize/2 + tableLeftBorder;
const float tableVerticalMiddle = verticalTableSize/2 + tableUpBorder;

const float frictionEffect = 0.01;
const float minVelocity = 0.05;

const std::vector<Pos> startingPositions = {
	{100, tableVerticalMiddle}, //white_ball
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

const std::vector<Color> ballColors = {
	{255, 255, 255, 255}, //white_ball
	{255, 255, 0, 255}, //ball 1, yellow
	{0, 0, 255, 255}, //ball 2
	{255, 0, 0, 255}, //ball 3
	{127, 0, 255, 255}, //ball 4
	{255, 128, 0, 255}, //ball 5
	{0, 102, 0, 255}, //ball 6
	{153, 0, 0, 255}, //ball 7
	{0, 0, 0, 255}, //ball 8
	{255, 255, 0, 255}, //ball 9, yellow
	{0, 0, 255, 255}, //ball 10
	{255, 0, 0, 255}, //ball 11
	{127, 0, 255, 255}, //ball 12
	{255, 128, 0, 255}, //ball 13
	{0, 102, 0, 255}, //ball 14
	{153, 0, 0, 255}, //ball 15
};

#endif