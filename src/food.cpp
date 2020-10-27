#include "food.h"
#include <time.h>
#include <iostream>

using namespace std;
    
// constructiors
Food::Food()
{
    updateType();
    _random = true;
    setActive(false);
    setVisible(false);
}

Food::Food(type t) : _foodtype(t)
{
    _random = false;
    setActive(true);
    setVisible(true);
}

// move constructor
Food::Food(Food&& f)
{
    lock_guard<mutex> lock(f._mtx);    
    _foodtype = f._foodtype;
    _random = f._random;
    _position = f._position;
    
    _active = f._active;
    _visible = f._visible;
    _flashing = f._flashing;
}

// Copy Constructor
Food::Food(const Food& f)
{
    lock_guard<mutex> lock(f._mtx);
    _foodtype = f._foodtype;
    _random = f._random;
    _position = f._position;
    
    _active = f._active;
    _visible = f._visible;
    _flashing = f._flashing;
}

// Move Assignmet
Food &Food::operator = (Food&& f)
{
    lock(_mtx, f._mtx);
    lock_guard<mutex> self_lock(_mtx, adopt_lock);
    lock_guard<mutex> other_lock(f._mtx, adopt_lock);
  
    _foodtype = move(f._foodtype);
    _random = move(f._random);
    _position = move(f._position);
    
    _active = move(f._active);
    _visible = move(f._visible);
    _flashing = move(f._flashing);
    return *this;
}

// Copy Assignmnet
Food &Food::operator = (const Food& f)
{
    lock(_mtx, f._mtx);
    lock_guard<mutex> self_lock(_mtx, adopt_lock);
    lock_guard<mutex> other_lock(f._mtx, adopt_lock);


    _foodtype = f._foodtype;
    _random = f._random;
    _position = f._position;
    
    _active = f._active;
    _visible = f._visible;
    _flashing = f._flashing;
    return *this;
}

// getters
SDL_Point Food::getPos() const {return _position;}
bool Food::isPoison() const { return (_foodtype == poison); }
bool Food::isNormal() const { return (_foodtype == normal); }
bool Food::isSuper() const { return (_foodtype == super); }
Food::type Food::getType() const {return _foodtype;}

bool Food::isActive() const 
{
    lock_guard<mutex> lock(_mtx);
    return _active;
}

bool Food::isVisible() const 
{
    lock_guard<mutex> lock(_mtx);
    return _visible;
}

bool Food::isFlashing() const 
{
    lock_guard<mutex> lock(_mtx);
    return _flashing;
}

// setters
void Food::setActive(bool state)
{
    lock_guard<mutex> lock(_mtx);
    _active = state;
}

void Food::setVisible(bool state)
{
    lock_guard<mutex> lock(_mtx);
    _visible = state;
}

void Food::setFlashing(bool state)
{
    lock_guard<mutex> lock(_mtx);
    _flashing = state;
}

void Food::setPos(int x, int y)
{
    if (isActive() && _random) // random foods don't get replaced when "eaten"
    {
        setActive(false);
        setVisible(false);
    }
    else
    {
        _position.x = x;
        _position.y = y;
        setActive(true);
        setVisible(true);
        if(_random) // start deactivatio timer tread if food is random
        {
            thread deactivation(&Food::DeactivationTimer, this);
            deactivation.detach();
        }

    }
}

void Food::updateType()
{
    // assigns a new food type if the _random variable is set to true.
    if (_random)
    {
        srand (time(NULL));
        switch (rand() % 3)
        {
            case 0: 
                _foodtype = normal;
                break;
            case 1: 
                _foodtype = super;
                break;
            case 2: 
                _foodtype = poison;
                break;
        }
    }
}

void Food::DeactivationTimer()
{
    // starts a timer that "deactivates" the food after a certain time
    this_thread::sleep_for(chrono::seconds(4));
    if (isActive())
    {
        setFlashing(true);
        thread flash(&Food::FlashingTimer, this);
        flash.detach();
        //mtx.unlcok();
        this_thread::sleep_for(chrono::seconds(4));
    }
    setActive(false);
    setVisible(false);
    setFlashing(false);
}

void Food::FlashingTimer()
{
    // toggels visibility if the flashing option is set. 
    while (isFlashing() && isActive())
    {
        setVisible(!isVisible());
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}