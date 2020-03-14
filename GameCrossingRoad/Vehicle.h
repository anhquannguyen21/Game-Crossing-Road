#pragma once

#include"Console.h"

class VEHICLE
{
protected:
	int _x;
	int _y;
	int _speed;
public:
	VEHICLE() 
	{ 
	_x = 0;
	_y = 0;
	}
	int X()
	{
		return _x;
	}
	int Y()
	{
		return _y;
	}
	int Speed()
	{
		return _speed; 
	}
	void setSpeed(int speed) 
	{
		_speed = speed;
	}
	void setX(int x)
	{
		_x = x; 
	}
	void setY(int y) 
	{ 
		_y = y; 
	}
	void drawVehicle()
	{
		goToXY(_x, _y);
	}
	VEHICLE& operator = (const VEHICLE &p);
};