#include "snake.h"
#include <cmath>
#include <iostream>
#include "game.h"

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + _grid_width, _grid_width);
  head_y = fmod(head_y + _grid_height, _grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!_growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    _growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { _growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Snake::HandleInput(SDL_Keycode key){
    if(_game->GetState()!=Game::State::running){
      return false;
    }
    if(key==_keys.down){
      ChangeDirection(Snake::Direction::kDown);
    }
    else if(key==_keys.left){
      ChangeDirection(Snake::Direction::kLeft);
    }
    else if(key==_keys.right){
      ChangeDirection(Snake::Direction::kRight);
    }
    else if(key==_keys.up){
      ChangeDirection(Snake::Direction::kUp);
    }
    else{
      return false;
    }
    return true;
}
void Snake::ChangeDirection(Snake::Direction targetDirection){
  if (direction != Snake::MakeOppositeDirection(targetDirection) || size == 1) direction = targetDirection;
  return;
}

Snake::Direction Snake::MakeOppositeDirection(Snake::Direction direction){
  switch(direction){
    case Snake::Direction::kDown:
      return Snake::Direction::kUp;
    case Snake::Direction::kUp:
      return Snake::Direction::kDown;
    case Snake::Direction::kLeft:
      return Snake::Direction::kRight;
    case Snake::Direction::kRight:
      return Snake::Direction::kLeft; 
  }
}