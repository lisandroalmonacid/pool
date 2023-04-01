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

#endif
