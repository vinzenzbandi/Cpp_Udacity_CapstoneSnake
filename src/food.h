#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

class Food
{
public:
    enum type{normal, super, poison};
    
    // constructiors
    Food();
    Food(type t);

    Food(Food&& f);
    Food(const Food& f);
    Food &operator = (Food&& f);
    Food &operator = (const Food& f);

    // methods
    SDL_Point getPos() const;
    bool isSuper() const;
    bool isPoison() const;
    bool isNormal() const;
    type getType() const;
    bool isActive() const;
    bool isVisible() const;

    void setPos(int x, int y);
    void updateType();
    
private:
    mutable mutex _mtx;

    type _foodtype;
    bool _random; // if true food type is random
    SDL_Point _position; // where the food is placed

    // these three variables are updated in sepeate threads and need to be protected by mutex
    bool _active;
    bool _visible;
    bool _flashing;

    void DeactivationTimer();
    void FlashingTimer();

};

#endif