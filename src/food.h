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
    bool isSuper() const;
    bool isPoison() const;
    bool isNormal() const;
    type getType() const;

    void setPos(int x, int y);
    void updateType();
    

private:
    type _foodtype;
    bool _random; // if true food type is random
    SDL_Point _position; // where the food is placed
};

#endif