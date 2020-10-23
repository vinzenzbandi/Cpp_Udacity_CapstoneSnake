#include "food.h"
#include <time.h>
#include <iostream>

using namespace std;
    
// constructiors
Food::Food()
{
    updateType();

    _random = true;
}

Food::Food(type t) : _foodtype(t)
{
    _random = false;
}

// getters
SDL_Point Food::getPos() const {return _position;}
bool Food::isPoison() const { return (_foodtype == poison); }
bool Food::isNormal() const { return (_foodtype == normal); }
bool Food::isSuper() const { return (_foodtype == super); }
Food::type Food::getType() const {return _foodtype;}

// setters
void Food::setPos(int x, int y)
{
    _position.x = x;
    _position.y = y;
    return;
}

void Food::updateType()
{
    if (_random)
    {
        srand (time(NULL));
        switch (rand() % 3)
        {
            case 0: 
                cout << "normal" << endl;
                _foodtype = normal;
                break;
            case 1: 
                cout << "super" << endl;
                _foodtype = super;
                break;
            case 2: 
                cout << "poison" << endl;
                _foodtype = poison;
                break;
        }
    }

}