#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) 
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) 
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) 
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() 
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, vector<Food> const &foods) {
  SDL_Color renderColor = {0, 0, 0};

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  renderColor = BLACK;
  SDL_SetRenderDrawColor(sdl_renderer, renderColor.r, renderColor.g, renderColor.b, 0xFF);
  SDL_RenderClear(sdl_renderer);

  RenderFood(foods);

  // Render snake's body
  renderColor = LIGHTBLUE;
  SDL_SetRenderDrawColor(sdl_renderer, renderColor.r, renderColor.g, renderColor.b, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    renderColor = BLUE;
  } else {
    renderColor = RED;
  }
  SDL_SetRenderDrawColor(sdl_renderer, renderColor.r, renderColor.g, renderColor.b, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderFood(vector<Food> const &foods)
{
  SDL_Color renderColor;
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  for (Food const &food : foods)
  {
    if(food.isVisible())
    {
      switch( food.getType() )
      {
        case Food::normal:
          renderColor = YELLOW;
         break;
        case Food::super:
          renderColor = RED;
          break;
        case Food::poison:
          renderColor = GREEN;
      }
    }
    else
    {
      renderColor = BLACK;
    }
    SDL_SetRenderDrawColor(sdl_renderer, renderColor.r, renderColor.g, renderColor.b, 0xFF);
    SDL_Point foodPos =  food.getPos();
    block.x = foodPos.x * block.w;
    block.y = foodPos.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  // Render food
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
