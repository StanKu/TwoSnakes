#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <SDL.h>
class Game;

class GController{
    public:
    GController(){};
    virtual bool HandleInput(SDL_Keycode key) = 0;
    // Data elements: not owning
    Game* _game=nullptr; // Pointer to the game to be able to get current state and switch states
};

class ControllerDispatcher{
    public:
    void DispatchControllerEvents();
    void AddController(GController* controller); // or unique pointer?
    ControllerDispatcher(Game* game):_game(game){};

    private:
    // Data elements: Not owning
    std::vector<GController*> _controllers;
    Game* _game; // Pointer to the game
};
class GameController : public GController{
    bool HandleInput(SDL_Keycode key) override;
};

#endif