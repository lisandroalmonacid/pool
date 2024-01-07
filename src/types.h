#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <cmath>
#include <vector>
#include <iostream>

struct Vector2d {
  double x;
  double y;

  // LOGICAL OPERATORS

  bool operator==(Vector2d v) { return (v.x == this->x && v.y == this->y); }
  bool operator!=(Vector2d v) { return (v.x != this->x || v.y != this->y); }

  // VECTOR OPERATORS

  Vector2d operator+(Vector2d v) { return {this->x + v.x, this->y + v.y}; }
  Vector2d operator-(Vector2d v) { return {this->x - v.x, this->y - v.y}; }
  Vector2d operator*(Vector2d v) { return {this->x * v.x, this->y * v.y}; }
  Vector2d operator/(Vector2d v) { return {this->x / v.x, this->y / v.y}; }
  double operator%(Vector2d v) { return {this->x * v.x + this->y * v.y}; } //this is the scalar product.

  // SCALAR OPERATORS

  Vector2d operator+(double f) { return {this->x + f, this->y + f}; }
  Vector2d operator-(double f) { return {this->x - f, this->y - f}; }
  Vector2d operator*(double f) { return {this->x * f, this->y * f}; }
  Vector2d operator/(double f) { return {this->x / f, this->y / f}; }

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
  double norm() const {
      return sqrtf(powf(x, 2) + powf(y, 2));
  }
  double squareNorm() const {
      return powf(x, 2) + powf(y, 2);
  }
  Vector2d unitVector() {return *this/this->norm();}

  friend std::ostream& operator<<(std::ostream& os, const Vector2d& v) {
      os << "{" << v.x << ", " << v.y << "}";
      return os;
  }

};

typedef Vector2d Pos;
typedef Vector2d Vel;

enum Action {MainMenu, Pool, Quit};
enum BallClass {cueBall, Solid, Striped, Black, None};

struct Player {
  int _id;
  BallClass _ballClass;
};

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

typedef Color Pixel;

struct GameState {
    bool KEYS[322];  // 322 is the number of SDLK_DOWN events
    int mouseX;
    int mouseY;
    bool mouseClick;
    Action action;
};

enum PoolAction {Aim, Shoot, NextTurn};

#endif
