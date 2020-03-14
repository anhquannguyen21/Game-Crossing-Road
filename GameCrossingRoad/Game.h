#pragma once

#include"People.h"
#include"Truck.h"
#include"Car.h"
#include "Bird.h"
#include "Dinausor.h"

#define MAX_TRUCK_LENGTH 4
#define MAX_CAR_LENGTH 4
#define MAX_BIRD_LENGTH 3
#define MAX_DINAUSOR_LENGTH 3
#define MAX_TRUCK 17
#define MAX_CAR 15
#define MAX_BIRD 12
#define MAX_DINAUSOR 12
#define MAX_SPEED 4
struct record
{
	clock_t t;
	char name[100];
};

class CGAME
{
protected:
	int SPEED;
	POINT*RESULT1;
	int nRESULT1;
	int STOP1;
	int nStop1;
	int MOVING1;
	CPEOPLE* play;
	CTRUCK **t;
	CCAR **c;
	CDINAUSOR**d;
	CBIRD**b;
	int n_Truck;
	int n_Car;
	int n_Bird;
	int n_Dinausor;
	clock_t beginTime, time;
	record top[5];
public:
	CGAME();
	~CGAME();
	void up() 
	{
		play->up();
	}
	void left() 
	{ 
		play->left();
	}
	void right()
	{
		play->right();
	}
	void down()
	{
		play->down(); 
	}
	CPEOPLE*  getPlayer()
	{
		return play;
	}
	int LoadData(char*s);
	void STOP();
	void DrawBoard(int x, int y, int width, int height);
	void startGame();
	void resetData();
	void exitGame(HANDLE t);
	void pauseGame(HANDLE t);
	void processDead();
	void processFinish();
	void drawTruck();
	void DrawLose();
	void drawCar();
	void drawDinausor();
	void processWin();
	void drawBird();
	void eraseBird();
	void eraseDinausor();
	void moveBird();
	void moveDinausor();
	void ProcessResult(POINT p);
	void SaveGames();
	bool isImpact(int);
	void moveTruck();
	void moveCar();
	void eraseTruck();
	void eraseCar();
	bool stopm(int i);
};