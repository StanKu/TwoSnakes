#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

/*   Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n"; */
Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
Snake snake1 = Snake(kGridWidth, kGridHeight, SDL_Point{kGridWidth/4, kGridHeight/2}, SDL_Color{0xA1,0x15,0x35,0x00},Snake::KeyBindings{SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT});
Snake snake2 = Snake(kGridWidth, kGridHeight, SDL_Point{3*kGridWidth/4, kGridHeight/2}, SDL_Color{0x35,0x85,0x50,0x00},Snake::KeyBindings{SDLK_w, SDLK_s, SDLK_a, SDLK_d});
//Player player1=Player(std::move(snake1),Player::KeyBindings{SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT});
//Player player2=Player(std::move(snake2),Player::KeyBindings{SDLK_w, SDLK_s, SDLK_a, SDLK_d});
Game game(kGridWidth, kGridHeight, std::move(snake1), std::move(snake2));
game.Run(renderer, kMsPerFrame);
  
  return 0;
}