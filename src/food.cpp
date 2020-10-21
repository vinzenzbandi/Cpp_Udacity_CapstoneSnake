#include "food.h"
#include <iostream>

using namespace std;
    
// constructiors
Food::Food()
{
    _foodtype = normal;
}

Food::Food(type t) : _foodtype(t)
{

}

// getters
SDL_Point Food::getPos() const {return _position;}
Food::type Food::getType() const {return _foodtype;}

// setters
void Food::setPos(int x, int y)
{
    _position.x = x;
    _position.y = y;
    cout << "food positioned at " << x << " " << y << endl;
    return;
}