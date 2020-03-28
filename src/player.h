#ifndef PLAYER_H
#define PLAYER_H

#include "controller.h"
#include "snake.h"
class Game;

class Player : public GController{
    public:   
    struct KeyBindings{
    SDL_Keycode up; // Key to change the direction to go up
    SDL_Keycode down; // Key to change the direction to go down
    SDL_Keycode left; // Key to change the direction to go left
    SDL_Keycode right; // Key to change the direction to go right
    };

    Player(Snake&& snake, KeyBindings keys): _snake(snake), _keys(keys){};
    bool HandleInput(SDL_Keycode key) override;
    Snake* getSnake(){return &_snake;}

    private:
    void ChangeDirection(Snake::Direction direction);

    // Data elements: Not owning
    
    // Data elements: Owning/primitives
    KeyBindings _keys;
    Snake _snake; // Controlled snake.
};

#endif