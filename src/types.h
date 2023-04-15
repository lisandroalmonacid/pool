#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <cmath>
#include <vector>
#include <iostream>

struct Vector2d {
  float x;
  float y;

  // LOGICAL OPERATORS

  bool operator==(Vector2d v) { return (v.x == this->x && v.y == this->y); }
  bool operator!=(Vector2d v) { return (v.x != this->x || v.y != this->y); }

  // VECTOR OPERATORS

  Vector2d operator+(Vector2d v) { return {this->x + v.x, this->y + v.y}; }
  Vector2d operator-(Vector2d v) { return {this->x - v.x, this->y - v.y}; }
  Vector2d operator*(Vector2d v) { return {this->x * v.x, this->y * v.y}; }
  Vector2d operator/(Vector2d v) { return {this->x / v.x, this->y / v.y}; }
  float operator%(Vector2d v) { return {this->x * v.x + this->y * v.y}; } //this is the scalar product.

  // SCALAR OPERATORS

  Vector2d operator+(float f) { return {this->x + f, this->y + f}; }
  Vector2d operator-(float f) { return {this->x - f, this->y - f}; }
  Vector2d operator*(float f) { return {this->x * f, this->y * f}; }
  Vector2d operator/(float f) { return {this->x / f, this->y / f}; }

  // ASSIGNMENT OPERATORS
  Vector2d operator=(Vector2d v) { 
    x = v.x;
    y = v.y;
    return *this;
  }

  Vector2d operator+=(Vector2d v) { 
    x += v.x;
    y += v.y;
    return *this;
  }

  Vector2d operator-=(Vector2d v) { 
    x -= v.x;
    y -= v.y;
    return *this;
  }

  // AUX

  float norm() {return sqrtf(powf(x, 2) + powf(y, 2));}
  float squareNorm() { return powf(x, 2) + powf(y, 2);}
  Vector2d unitVector() {return *this/this->norm();}

  friend std::ostream& operator<<(std::ostream& os, const Vector2d& v) {
      os << "{" << v.x << ", " << v.y << "}";
      return os;
  }

};

typedef Vector2d Pos;
typedef Vector2d Vel;

enum Action {mainMenu, game, quit};

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

typedef Color Pixel;

#endif
