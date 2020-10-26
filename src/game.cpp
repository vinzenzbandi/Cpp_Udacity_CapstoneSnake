#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)-1 ),
      random_h(0, static_cast<int>(grid_height)-1 ) {
  foods.emplace_back(move(Food(Food::normal)));
  foods.emplace_back(move(Food()));
  PlaceFood(foods.at(0));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  Uint32 food_timestamp = SDL_GetTicks();
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, foods);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    // every 20 seconds place a random food
    if (frame_end - food_timestamp >= 20000)
    {
      PlaceFood(foods.at(1));
      food_timestamp = frame_end;
    }
  }
}

void Game::PlaceFood( Food &food ) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.setPos(x,y);
      food.updateType();
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  for(Food &food : foods)
  {
    // Check if there's food over here
    if (food.getPos().x == new_x && food.getPos().y == new_y && food.isActive()) 
    {
      // increase score and grow body according to food type
      if (food.isNormal())
      {
        score++;
        snake.GrowBody();
      }
      else if(food.isSuper())
      {
        score += 2;
      }
      else
      {
        score --;
        snake.GrowBody();
      }
      
      // Grow snake and place new food.
      PlaceFood(food);
      snake.speed += 0.01;
    }
  }

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }