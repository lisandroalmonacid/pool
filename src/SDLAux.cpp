#include "SDLAux.h"
#include "physics.h"
#include "Ball.h"
#include <fstream>
#include <iostream>
#include <bitset>

void drawCircle(Pos center, float radius, Color Color) {

    SDL_SetRenderDrawColor(rend, Color.r, Color.g, Color.b, Color.a);
    int maxPointsCount = int(4*radius*radius); //round-up pi.
    SDL_Point* points = (SDL_Point*) malloc(maxPointsCount * sizeof(SDL_Point));

    if (points != nullptr) {
        int pointsCount = 0;    
        //draw square only if distance is less than radius.
        Pos up_left = {center.x - radius, center.y - radius};

        for (int x = up_left.x; x < up_left.x + 2 * radius; x++) {
            for (int y = up_left.y; y < up_left.y + 2 * radius; y++) {
                float distX = x - center.x;
                float distY = y - center.y;
                float norm = sqrt(pow(distX, 2) + pow(distY, 2));
                if (std::abs(radius-norm) < 2 && pointsCount < maxPointsCount) {
                    points[pointsCount] = {x, y};
                    pointsCount++;
                }
            }
        }
        if (SDL_RenderDrawPoints(rend, points, pointsCount) > 0) {
            std::cout << SDL_GetError() << std::endl;
        }
        
    }
    free(points);
}

void drawRect(Pos startPos, int width, int height, Color color) {
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {startPos.x, startPos.y, width, height};
    SDL_RenderFillRect(rend, &rect);
}

void drawMainMenuScreen() {
    //drawBMP(rend, {0, vertical_screen_size}, "../img/mainMenu.bmp");
    //SDL_BlitSurface(mainMenuSurface, nullptr, screenSurface, nullptr);
    //drawRect({0, 0}, screenW, verticalScreenSize, {255, 255, 255, 255});
    //SDL_UpdateWindowSurface(win);
}

void drawTable() {}

void drawBalls(Ball* balls) {}

void drawCue(Ball* balls) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rect = {mouseX, mouseY, balls[0].pos.x - mouseX, balls[0].pos.y - mouseY};
    //SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 255, 0, 0));
}

void drawBMP(Pos startPos, char* filepath) {}

void drawWallCollision(Ball* b, Pos l1, Pos l2) {
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 0);
    SDL_RenderDrawLine(rend, l1.x, l1.y, l2.x, l2.y);
    SDL_Rect rect = {b->pos.x - ballRadius, b->pos.y - ballRadius, ballRadius*2,ballRadius*2};
    SDL_RenderDrawRect(rend, &rect);
    SDL_RenderPresent(rend);
    SDL_Delay(50);
}

void drawBallCollision(Ball* b1, Ball* b2) {
    tableTexture->draw({0, 0});
    b1->draw();
    b2->draw();
    SDL_RenderDrawLine(rend, b1->pos.x, b1->pos.y, b2->pos.x, b2->pos.y);
    SDL_RenderDrawLine(rend, b1->pos.x, b1->pos.y, b1->pos.x + b1->vel.x*ballRadius, b1->pos.y + b1->vel.y * ballRadius);
    SDL_RenderDrawLine(rend, b2->pos.x, b2->pos.y, b2->pos.x + b2->vel.x, b2->pos.y + b2->vel.y * ballRadius);

    SDL_RenderPresent(rend);
    SDL_Delay(10000);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);
}

void drawBallTrajectory(std::vector<Ball*> balls, float mouseX, float cueAngle) {
    //draw projected ball trajectory
    int maxLineLen = pointsNorm({0, 0}, {screenW, screenH});
    float lineAngle = balls[0]->pos.x > mouseX ? cueAngle : cueAngle + M_PI;
    Pos lineEnd = {balls[0]->pos.x + maxLineLen*cos(cueAngle), balls[0]->pos.y + maxLineLen*sin(cueAngle)};
    
    Pos iWallMin = {-10000, -10000};
    for (int i = 1; i < 25; i++) {
        Vector2d dWall = {tableEdges[i].x - tableEdges[i-1].x, tableEdges[i].y - tableEdges[i-1].y};
        Pos iWall = intersection({cos(cueAngle), sin(cueAngle)}, balls[0]->pos, dWall, tableEdges[i]);
        if ( isPointInLine(iWall, balls[0]->pos, lineEnd) &&
                isPointInLine(iWall, tableEdges[i-1], tableEdges[i]) &&
                (iWall.x != -1 && iWall.y != -1) && 
                (pointsNorm(iWall, balls[0]->pos) < pointsNorm(iWallMin, balls[0]->pos)) ) {
            iWallMin = iWall;
            }
    }

    Pos iBallMin = {-10000, -10000};

    for (int i = 1; i < balls.size(); i++) {
        if (isBallCollidingWithWall(balls[i], balls[0]->pos, lineEnd)) {
            Pos impactPoint = {balls[i]->pos.x - ballRadius*cos(lineAngle),
                                balls[i]->pos.y - ballRadius*sin(lineAngle)};
            if (pointsNorm(balls[0]->pos, impactPoint) < pointsNorm(balls[0]->pos, iBallMin)) {
                iBallMin = impactPoint;
            }
        }
    }

    if (pointsNorm(balls[0]->pos, iWallMin) < pointsNorm(balls[0]->pos, iBallMin)) {
        Pos center = {iWallMin.x - cos(lineAngle)*ballRadius, iWallMin.y - sin(lineAngle)*ballRadius};
        drawCircle(center, ballRadius, {0, 0, 0, 255});
        SDL_RenderDrawLine(rend, balls[0]->pos.x,
                                    balls[0]->pos.y,
                                    center.x,
                                    center.y);
    } else {
        Pos center = {iBallMin.x - cos(lineAngle)*ballRadius, iBallMin.y - sin(lineAngle)*ballRadius};
        drawCircle(center, ballRadius, {0, 0, 0, 255});
        SDL_RenderDrawLine(rend, balls[0]->pos.x, balls[0]->pos.y, center.x, center.y);
    }
}

SDL_Texture* createTextTexture(TTF_Font* font, char* text, SDL_Color color) {
    SDL_Surface* tmp = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, tmp);
    SDL_FreeSurface(tmp);
    tmp = nullptr;
    return texture;
}