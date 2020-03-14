#pragma once
#include "Console.h"
class CANIMAL
{
	int _x;
	int _y;
	int _speed;
public:
	CANIMAL()
	{
		_x = 0;
		_y = 0;
	}
	int Speed()
	{
		return _speed;
	}
	void setSpeed(int otherspeed)
	{
		_speed = otherspeed;
	}
	int X()
	{
		return _x;
	}
	int Y()
	{
		return _y;
	}
	void setX(int x)
	{
		_x = x;
	}
	void setY(int y)
	{
		_y = y;
	}
	void drawAnimal()
	{
		goToXY(_x, _y);
	}
	CANIMAL& operator = (const CANIMAL &p);
};

