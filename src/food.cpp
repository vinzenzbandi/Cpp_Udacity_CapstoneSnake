#include "food.h"
#include <time.h>
#include <iostream>

using namespace std;
    
// constructiors
Food::Food()
{
    updateType();
    _random = true;
    _active = false;
    _visible = false;
}

Food::Food(type t) : _foodtype(t)
{
    _random = false;
    _active = true;
    _visible = true;
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

bool Food::isActive() const {return _active;}
bool Food::isVisible() const {return _visible;}

// setters
void Food::setPos(int x, int y)
{
    //mtx.lock()
    if (_active && _random) // random foods don't get replaced when "eaten"
    {
        _active = false;
        _visible = false;
    }
    else
    {
        _position.x = x;
        _position.y = y;
        _active = true;
        _visible = true;
        if(_random)
        {
            thread deactivation(&Food::DeactivationTimer, this);
            deactivation.detach();
        }

    }
    //mtx.unlock();
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

void Food::DeactivationTimer()
{
    this_thread::sleep_for(chrono::seconds(4));
    //mtx.lcok();
    if (this->isActive())
    {
        _flashing = true;
        thread flash(&Food::FlashingTimer, this);
        flash.detach();
        //mtx.unlcok();
        this_thread::sleep_for(chrono::seconds(4));
    }
    _active = false;
    _visible = false;
    _flashing = false;
    //mtx.unlock();
}

void Food::FlashingTimer()
{
    while (_flashing && _active)
    {
        _visible = !_visible;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}