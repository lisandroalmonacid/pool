#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <cmath>
#include <vector>

struct Pos {
  float x;
  float y;
};

struct Vel {
  float x;
  float y;
};

struct Ball {
  Pos pos;
  Vel vel;
  bool isIn;
};

enum Action {mainMenu, game, quit};

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct BMPHeader {
  char signature[3];
  char filesize[5];
  char reserved[5];
  char dataOffset[5];
};

struct BMPInfoHeader {
  char size[5];
  char width[5];
  char height[5];
  uint16_t planes;
  uint16_t bitsPerPixel;
  uint32_t compression;
  uint32_t imageSize;
  uint32_t xPixelsPerM;
  uint32_t yPixelsPerM;
  uint32_t colorsUsed;
  uint32_t importantColors;
  uint32_t* colorTable;
};

struct BMP {
  BMPHeader header;
  BMPInfoHeader infoHeader;
  Pixel* pixelData;

};


#endif
