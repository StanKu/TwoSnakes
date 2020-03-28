#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "controller.h"

class Game;

class Snake : public GController {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  struct KeyBindings{
    SDL_Keycode up; // Key to change the direction to go up
    SDL_Keycode down; // Key to change the direction to go down
    SDL_Keycode left; // Key to change the direction to go left
    SDL_Keycode right; // Key to change the direction to go right
    };

  Snake(int grid_width, int grid_height, SDL_Color color, KeyBindings keys)
      : _grid_width(grid_width),
        _grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        _color(color),
        _keys(keys) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  SDL_Color getColor(){return _color;}
  bool HandleInput(SDL_Keycode key) override;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
    // Data elements: Owning/primitives
  SDL_Color _color;
  int score=0;
  // Data elements: not owning
  Game* _game;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void ChangeDirection(Snake::Direction direction);
  static Snake::Direction MakeOppositeDirection(Snake::Direction direction);
  bool _growing{false};
  int _grid_width;
  int _grid_height;
  KeyBindings _keys;
};

#endif