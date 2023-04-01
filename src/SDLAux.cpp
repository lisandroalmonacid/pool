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
                if (int(norm) <= radius && pointsCount < maxPointsCount) {
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
    SDL_BlitSurface(mainMenuSurface, nullptr, screenSurface, nullptr);
    //drawRect({0, 0}, horizontalScreenSize, verticalScreenSize, {255, 255, 255, 255});
    SDL_UpdateWindowSurface(win);
}

void drawTable() {
    SDL_BlitSurface(tableSurface, nullptr, screenSurface, nullptr);
}

void drawBalls(Ball* balls) {
    //update dst rectangles
    for (int i = 0; i < 16; i++) {
        dst_rects[i].x = balls[i].pos.x - ballRadius;
        dst_rects[i].y = balls[i].pos.y - ballRadius;
        dst_rects[i].w = ballRadius * 2;
        dst_rects[i].h = ballRadius * 2;
    }

    //draw balls
    for(int i = 0; i < 16; i++) {
        SDL_BlitScaled(ballsSurface, &src_rects[i], screenSurface, &dst_rects[i]);
    }
}

void drawCue(Ball* balls) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Rect rect = {mouseX, mouseY, balls[0].pos.x - mouseX, balls[0].pos.y - mouseY};
    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 255, 0, 0));
}

void drawBMP(Pos startPos, char* filepath) {}