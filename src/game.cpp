#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, Snake&& player1, Snake&& player2):
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      _player1(player1),
      _player2(player2),
      _player1_init(player1),
      _player2_init(player2),
      _dispatcher(this),
      _state(help){
    _player1._game=this;
    _player2._game=this;
    _player1_init._game=this;
    _player2_init._game=this;
    _controller._game=this;  
    _dispatcher.AddController(&_player1);
    _dispatcher.AddController(&_player2);
    _dispatcher.AddController(&_controller);
    
  PlaceFood();
}

void Game::SetState(Game::State state){
  _state=state;
}

std::vector<Snake*> Game::getSnakes(){
  std::vector<Snake*> snakes;
  snakes.push_back(&_player1);
  snakes.push_back(&_player2);
  return snakes;
}

void Game::Run(Renderer& renderer, std::size_t target_frame_duration){
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while(_state!=exiting){
    if(_state==reset){
      // Reset the snakes
      _player1=_player1_init;
      _player2=_player2_init;
      SetState(running);
    }
    frame_start = SDL_GetTicks();
    _dispatcher.DispatchControllerEvents();
    if(_state==running) Update();
    renderer.Render(this);
  frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(this, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_player1.SnakeCell(x, y)&&!_player2.SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::Update(){
  if(_state!=running) return;
  for(Snake* snake:getSnakes()){
  snake->Update();
  // Check if snake died
  if(!snake->alive){
    SetState(finished);
    return;
  }
  // Check if there's food over here
  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);
  if (_food.x == new_x && _food.y == new_y) {
    snake->score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }}
}