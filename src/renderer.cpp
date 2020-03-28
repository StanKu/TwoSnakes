#include "renderer.h"
#include <iostream>
#include <string>
#include "game.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Two Snakes", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Load help splash
  auto helpimage=SDL_LoadBMP("res/help.bmp");
    if(helpimage!=NULL){
      sdl_helpscreen = SDL_CreateTextureFromSurface(sdl_renderer,helpimage);
      SDL_SetTextureAlphaMod(sdl_helpscreen,180);
      SDL_SetTextureBlendMode(sdl_helpscreen,SDL_BLENDMODE_BLEND);
      SDL_FreeSurface(helpimage);
    }
}

Renderer::~Renderer() {
  SDL_DestroyTexture(sdl_helpscreen);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Game* game) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = game->getFood().x * block.w;
  block.y = game->getFood().y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  for(Snake* snake:game->getSnakes()){
  SDL_SetRenderDrawColor(sdl_renderer, snake->_color.r+lighterBody, snake->_color.g+lighterBody, snake->_color.b+lighterBody, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, snake->_color.r, snake->_color.g, snake->_color.b, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, snake->_color.r, snake->_color.g, snake->_color.b, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render help
  if(game->GetState()==Game::State::help){
    SDL_RenderCopy(sdl_renderer,sdl_helpscreen,NULL,NULL);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);

}

void Renderer::UpdateWindowTitle(Game* game, int fps) {
  std::string title{"Two Snakes Red: " + std::to_string(game->getSnakes()[0]->score) + " Green: " + std::to_string(game->getSnakes()[1]->score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
