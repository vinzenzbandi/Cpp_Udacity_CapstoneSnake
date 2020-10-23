#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, vector<Food> const &foods);
  void UpdateWindowTitle(int score, int fps);

 private:
  void RenderFood(vector<Food> const &foods);

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  // Colors
  static constexpr SDL_Color WHITE = {0xFF, 0xFF, 0xFF};
  static constexpr SDL_Color BLUE = {0x00, 0x7A, 0xCC};
  static constexpr SDL_Color LIGHTBLUE = {0x22, 0x97, 0xDD};
  static constexpr SDL_Color YELLOW = {0xFF, 0xCC, 0x00};
  static constexpr SDL_Color RED = {0xFF, 0x00, 0x00};
  static constexpr SDL_Color BLACK = {0x1E, 0x1E, 0x1E};
  static constexpr SDL_Color GREEN = {0x00, 0xFF, 0x00};
};

#endif