#include "SDLAux.h"
#include <fstream>
#include <iostream>
#include <bitset>

void drawCircle(SDL_Renderer* rend, Pos center, float radius, Color Color) {

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

void drawRect(SDL_Renderer* rend, Pos startPos, int width, int height, Color color) {
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    int maxPointsCount = (width + 1) * (height + 1);
    SDL_Point* points = (SDL_Point*) malloc(maxPointsCount * sizeof(SDL_Point));

    if (points != nullptr) {
        int pointsCount = 0;

        for (int x = startPos.x; x < startPos.x + width; x++) {
            for (int y = startPos.y; y < startPos.y + height; y++) {
                if (pointsCount < maxPointsCount) {
                    //std::cout << "x: " << x << ". y: " << y << ". Count: " << pointsCount << std::endl;
                    points[pointsCount] = {x, y};
                    pointsCount++;
                }
            }
        }
        SDL_RenderDrawPoints(rend, points, pointsCount);
    }
    free(points);

}

void drawMainMenuScreen(SDL_Renderer* rend) {
    //drawBMP(rend, {0, vertical_screen_size}, "../img/mainMenu.bmp");
    drawRect(rend, {0, 0}, horizontalScreenSize, verticalScreenSize, {255, 255, 255, 255});
    SDL_RenderPresent(rend);
}

void drawTable(SDL_Renderer* rend, SDL_Surface* screenSurface) {
    //draw outer brown rectangle
    // drawRect(rend, {0, 0}, horizontalScreenSize, verticalScreenSize, {110, 38, 14, 255});
    // drawRect(rend, {ballRadius * 2, ballRadius * 2}, horizontalTableSize, verticalTableSize, {0, 128, 0, 255});

    SDL_Rect brownRect = {0, 0, horizontalScreenSize, verticalScreenSize};
    SDL_FillRect(screenSurface, &brownRect , SDL_MapRGBA(screenSurface->format, 100, 38, 14, 255));
    
    SDL_Rect greenRect =  {ballRadius * 2, ballRadius * 2, horizontalTableSize, verticalTableSize};
    SDL_FillRect(screenSurface, &greenRect, SDL_MapRGBA(screenSurface->format, 100, 38, 14, 255));

    //draw holes
    drawCircle(rend, {ballRadius, ballRadius}, ballRadius, {0, 0, 0, 255});
}

void drawBalls(SDL_Renderer* rend, Ball* balls) {
        for(int i = 0; i < 16; i++) {
            drawCircle(rend, balls[i].pos, ballRadius, ballColors[i]);
        }
}

void drawBMP(SDL_Renderer* rend, Pos startPos, char* filepath) {
/*    BMP bmp;

    std::ifstream bmp_file;
    bmp_file.open(filepath, std::ios::in | std::ios::binary);


    std::cout << "--HEADER--" << std::endl;

    bmp_file.read(bmp.header.signature, 2);
    bmp.header.signature[2] = '\0';
    std::cout << "Signature: " << bmp.header.signature << std::endl;

    bmp_file.read(bmp.header.filesize, 4);
    bmp.header.filesize[5] = '\0';
    std::cout << "FileSize: " << bmp.header.filesize << std::endl;

    bmp_file.read(bmp.header.reserved, 4);
    bmp.header.reserved[4] = '\0';
    std::cout << "Reserved: " << bmp.header.reserved << std::endl;

    bmp_file.read(bmp.header.dataOffset, 4);
    bmp.header.dataOffset[5] = '\0';
    std::cout << "Data Offset: " << bmp.header.dataOffset << std::endl;

    std::cout << "--INFO HEADER--" << std::endl;

    bmp_file.read(bmp.infoHeader.size, 4);
    bmp.infoHeader.size[5] = '\0';
    std::cout << "Info header size: " << bmp.infoHeader.size << std::endl;

    bmp_file.read(bmp.infoHeader.width, 4);
    bmp.infoHeader.width[5] = '\0';
    std::cout << "Img Width: " << bmp.infoHeader.width << std::endl;

    bmp_file.read(bmp.infoHeader.height, 4);
    bmp.infoHeader.height[5] = '\0';
    std::cout << "Img Height: " << bmp.infoHeader.height << std::endl;



  uint16_t planes;
  uint16_t bitsPerPixel;
  uint32_t compression;
  uint32_t imageSize;
  uint32_t xPixelsPerM;
  uint32_t yPixelsPerM;
  uint32_t colorsUsed;
  uint32_t importantColors;
  uint32_t* colorTable;
  Pixel* pixelData;

    //leimos 22 bytes, faltan leer dataOffset - 22 para llegar a lo que nos interesa.

    char r[4];
    char g[4];
    char b[4];

    for (int y = startPos.y; y > startPos.y - bmp.height; y--) {
        for (int x = startPos.x; x < startPos.x + bmp.width; x++) {
            bmp_file.read(r, 4);
            bmp_file.read(g, 4);
            bmp_file.read(b, 4);

            SDL_SetRenderDrawColor(rend, int(r), int(g), int(b), 255);
            SDL_RenderDrawPoint(rend, x, y);
        }
    }
    bmp_file.close();
*/    
}