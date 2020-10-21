#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

using namespace std;

class Food
{
public:
    enum type{normal, super, poison};
    
    // constructiors
    Food();
    Food(type t);

    // methods
    SDL_Point getPos() const;
    void setPos(int x, int y);
    type getType() const;
    

private:
    type _foodtype;
    SDL_Point _position; // where the food is placed
};

#endif