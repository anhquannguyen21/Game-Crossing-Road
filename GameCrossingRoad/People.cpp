#include"People.h"

void CPEOPLE::drawSpace()
{
	goToXY(_x, _y);
	cout << " ";
}

void CPEOPLE::drawPlayer()
{
	goToXY(_x, _y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 - _level);
	cout << "Y";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void CPEOPLE::up()
{
	if (_y > 1)
	{
		drawSpace();
		_y--;
		drawPlayer();
	}
}
void CPEOPLE::down()
{
	if (_y < 19)
	{
		drawSpace();
		_y++;
		drawPlayer();
	}
}
void CPEOPLE::left()
{
	if (_x > 1)
	{
		drawSpace();
		_x--;
		drawPlayer();
	}
}

void CPEOPLE::right()
{
	if (_x < 79)
	{
		drawSpace();
		_x++;
		drawPlayer();
	}
}

