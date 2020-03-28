#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "player.h"

class Game {
 public:

enum State{
  help, // Help screen shown
  running, // Game is running, snakes are moving
  finished, // Game finished, final score displayed
  exiting // Game is about to exit
};

  Game(std::size_t grid_width, std::size_t grid_height, Player&& player1, Player&& player2);
  //void Run(Controller const &controller, Renderer &renderer,
  //         std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  State GetState()const{return _state;};
  void SetState(State state);

  void Run(Renderer& renderer, std::size_t target_frame_duration);

  SDL_Point getFood()const{return _food;}
  Player& getPlayer1(){return _player1;}
  Player& getPlayer2(){return _player2;}
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
  Player _player1;
  Player _player2;
  ControllerDispatcher _dispatcher;
  GameController _controller;
};

#endif