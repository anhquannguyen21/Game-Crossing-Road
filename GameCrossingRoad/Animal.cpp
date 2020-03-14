#include "Animal.h"

CANIMAL& CANIMAL::operator = (const CANIMAL &p)
{
	_x = p._x;
	_y = p._y;
	_speed = p._speed;
	return *this;
}