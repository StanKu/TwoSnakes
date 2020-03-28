#include "player.h"
#include "game.h"

bool Player::HandleInput(SDL_Keycode key){
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
void Player::ChangeDirection(Snake::Direction direction){
  if (_snake.direction != Snake::Direction::kDown || _snake.size == 1) _snake.direction = direction;
  return;
}