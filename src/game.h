#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:

enum State{
  help, // Help screen shown
  running, // Game is running, snakes are moving
  finished, // Game finished, final score displayed
  exiting, // Game is about to exit
  reset // Game has to be reset to start again
};

  Game(std::size_t grid_width, std::size_t grid_height, Snake&& player1, Snake&& player2);
  //void Run(Controller const &controller, Renderer &renderer,
  //         std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  State GetState()const{return _state;};
  void SetState(State state);

  void Run(Renderer& renderer, std::size_t target_frame_duration);

  SDL_Point getFood()const{return _food;}
  std::vector<Snake*> getSnakes();

 private:
  SDL_Point _food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();

  
  // Data elements: Owning/primitives
  State _state;
  Snake _player1, _player1_init;
  Snake _player2, _player2_init;
  ControllerDispatcher _dispatcher;
  GameController _controller;
};

#endif