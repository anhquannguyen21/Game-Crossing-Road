#pragma once

#include"Console.h"

class CPEOPLE
{
private:
	int _x;
	int _y;
	bool _state;
	int _level;
public:
	CPEOPLE(int x, int y, int z)
	{
		_x = x;
		_y = y;
		_state = 0;
		_level = z; 
	}
	bool State() 
	{
		return _state;
	}
	int Level()
	{ 
		return _level;
	}
	void setState(bool x)
	{ 
		_state = x;
	}
	void setXY(int x, int y) 
	{
		_x = x;
		_y = y;
	}
	void setLevel(int x) 
	{
		_level = x;
	}
	int X()
	{ 
		return _x;
	}
	int Y()
	{
		return _y;
	}
	void drawSpace();
	void drawPlayer();
	void up();
	void left();
	void right();
	void down();
};