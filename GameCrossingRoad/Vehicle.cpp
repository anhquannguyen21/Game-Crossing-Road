#include"Vehicle.h"

VEHICLE& VEHICLE::operator = (const VEHICLE &p)
{
	_x = p._x;
	_y = p._y;
	_speed = p._speed;
	return *this;
}