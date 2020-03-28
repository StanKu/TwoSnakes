#include "controller.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include "game.h"

bool GameController::HandleInput(SDL_Keycode key){
  // If any key is pressed during the help screen the game resumes
  if(_game->GetState()==Game::State::help){
    _game->SetState(Game::running);
    return true;
  }
  else{
    if(key==SDLK_F1){
      _game->SetState(Game::help);
      return true;
    }else if(key==SDLK_ESCAPE){
      _game->SetState(Game::exiting);
      return true;
    }
  }
  return false;
}

void ControllerDispatcher::AddController(GController* controller){
  _controllers.push_back(controller);
}

void ControllerDispatcher::DispatchControllerEvents(){
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      _game->SetState(Game::State::exiting);
    } else if (e.type == SDL_KEYDOWN) {
      auto key = e.key.keysym.sym; 
      
      for(auto c:_controllers){
        if(c->HandleInput(key)) break;
      }
    }
  }
}