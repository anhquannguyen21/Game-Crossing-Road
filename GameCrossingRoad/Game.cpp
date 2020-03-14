#include"Game.h"
#include "rlutil.h"
CGAME::CGAME()
{
	MOVING1 = 'D';
	SPEED = 1;
	play= new CPEOPLE(18, 19, 0);
	int tempCar[100];
	int tempTruck[100];
	n_Truck = 10;
	n_Car = 10;
	play = new CPEOPLE(18, 19, 0);
	t = new CTRUCK*[MAX_TRUCK];
	for (int i = 0; i < MAX_TRUCK; i++)
		t[i] = new CTRUCK[MAX_TRUCK_LENGTH];
	for (int i = 0; i <MAX_TRUCK; i++)
	{
		tempTruck[i] = (rand() % (WIDTH_CONSOLE - MAX_TRUCK_LENGTH)) + 1;
		for (int j = 0; j < MAX_TRUCK_LENGTH; j++)
		{
			t[i][j].setX(tempTruck[i] + j);
			t[i][j].setY(2 + i);
			t[i][j].setSpeed(1);
		}
	}
	c = new CCAR*[MAX_CAR];
	for (int i = 0; i < MAX_CAR; i++)
		c[i] = new CCAR[MAX_CAR_LENGTH];
	for (int i = 0; i< MAX_CAR; i++)
	{
		if (i < MAX_TRUCK)
		do
		tempCar[i] = (rand() % (WIDTH_CONSOLE - MAX_CAR_LENGTH)) + 1;
		while (abs(tempTruck[i] - tempCar[i]) <= 6);
		else
			tempCar[i] = (rand() % (WIDTH_CONSOLE - MAX_CAR_LENGTH)) + 1;
		for (int j = 0; j < MAX_CAR_LENGTH; j++)
		{
			c[i][j].setX(tempCar[i] + j);
			c[i][j].setY(2 + i);
			c[i][j].setSpeed(1);
		}
	}
	if (RESULT1)delete[]RESULT1;
	RESULT1 = new POINT;
	nRESULT1 = 0;
	STOP1 = rand() % (MAX_CAR - 1);
	nStop1 = 0;
}
int CGAME::LoadData(char *s)
{
	MOVING1 = 'D';
	FILE*f;
	fopen_s(&f, s, "rb");
	if (f){
		fread(&STOP1, sizeof(int), 1, f);
		fread(&nStop1, sizeof(int), 1, f);
		fread(&SPEED, sizeof(int), 1, f);
		fread(&play, sizeof(play), 1, f);
		if (c == 0){
			c = new CCAR*[MAX_CAR];
			for (int i = 0; i < MAX_CAR; i++)
				c[i] = new CCAR[MAX_CAR_LENGTH];
		}

		for (int i = 0; i<MAX_CAR; i++)
		for (int j = 0; j<MAX_CAR_LENGTH; j++)
		{
			fread(&c[i][j], sizeof(c[i][j]), 1, f);
		}
		fread(&nRESULT1, sizeof(int), 1, f);
		if (RESULT1 == 0){
			RESULT1 = new POINT[nRESULT1];
		}
		for (int i = 0; i<nRESULT1; i++){
			fread(&RESULT1[i], sizeof(POINT), 1, f);
		}
		system("cls");
		for (int i = 0; i<nRESULT1; i++){
			goToXY(RESULT1[i].x, 1);
			cout << "Y";
		}
		DrawBoard(0, 0, WIDTH_CONSOLE+6, HEIGH_CONSOLE);
		play->setState(1);
		fclose(f);
		return 1;
	}
	return 0;
}

void CGAME::DrawLose()
{
	FILE*f;
	fopen_s(&f, "lose.txt", "r");
	int ch;
	goToXY(0, 0);
	while (1){
		ch = fgetc(f);
		if (!feof(f)){
			cout << (char)ch;
		}
		else break;
	}
	fclose(f);
}

void CGAME::ProcessResult(POINT p)
{

	POINT*temp = (POINT*)realloc(RESULT1, (nRESULT1 + 1)*sizeof(POINT));

	if (temp){

		RESULT1 = temp;
		RESULT1[nRESULT1].x = p.x;
		RESULT1[nRESULT1].y = p.y;
		nRESULT1++;
	}
}
CGAME::~CGAME()
{
	delete play;
	for (int i = 0; i < n_Truck; i++)
	{
		delete t[i];
	}
	for (int i = 0; i < n_Car; i++)
	{
		delete c[i];
	}
	for (int i = 0; i < n_Bird; i++)
	{
		delete b[i];
	}
	for (int i = 0; i < n_Dinausor; i++)
	{
		delete d[i];
	}
	delete[] t;
	delete[] c;
	delete[]b;
	delete[]d;
}
void CGAME::SaveGames()
{
	char s[20];
	goToXY(8, 8);
	cout << "Enterthefilename:";
	cin.getline(s, 20);
	FILE*f;
	fopen_s(&f, s, "wb+");
	if (f){
		fwrite(&STOP1, sizeof(int), 1, f);
		fwrite(&nStop1, sizeof(int), 1, f);
		for (int i = 0; i < MAX_CAR; i++);
		fwrite(&nRESULT1, sizeof(int), 1, f);
		for (int i = 0; i<nRESULT1; i++){
			fwrite(&RESULT1[i], sizeof(RESULT1[i]), 1, f);
		}
	}
	fclose(f);
}
void CGAME::startGame()
{
	clrscr();
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	play->setState(1);
	play->setXY(18, 19);
	play->drawPlayer();
	TextColor(14 - play->Level());
	goToXY(40, 26);
	cout << "Level: " << play->Level() + 1;
}

void CGAME::exitGame(HANDLE t)
{
	clrscr();
	TerminateThread(t, 0);
}

void CGAME::pauseGame(HANDLE t)
{
	SuspendThread(t);
}

void CGAME::processDead()
{
	play->setState(0);
	goToXY(5, HEIGH_CONSOLE + 6);
	cout << ("Dead,Type y to continue or any key to exit!");
}
void CGAME::processWin()
{
	char s[120];
	clrscr();
	ifstream file("graphWon.txt");
	for (int count = 0; count < 10; count++)
	{
		file.seekg(0);
		goToXY(0, 3);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 16);
		for (int i = 1; i <= 17; i++)
		{
			file.getline(s, 120);
			puts(s);
		}
		Sleep(200);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	goToXY(45, 23);
	cout << "Press Y or R to restart game";
	goToXY(50, 25);
	cout << "Press Ecs to exit game";
	play->setState(0);
}
void CGAME::processFinish()
{
	play->setLevel(play->Level() + 1);
	TextColor(14 - play->Level());
	goToXY(40, 26);
	if (play->Level() == MAX_SPEED)
	{
		processWin();
	}
	cout << "Level: " << play->Level() + 1;
	if (play->Level() == MAX_SPEED)
	{
		processWin();
	}
	for (int i = 0; i < n_Truck; i++)
	for (int j = 0; j < MAX_TRUCK_LENGTH; j++)
	{
		int temp = t[i][j].Speed();
		if (temp == MAX_SPEED)
			t[i][j].setSpeed(1);
		else
			t[i][j].setSpeed(temp + 1);
	}
	for (int i = 0; i < n_Car; i++)
	for (int j = 0; j < MAX_CAR_LENGTH; j++)
	{
		int temp = c[i][j].Speed();
		if (temp == MAX_SPEED)
			c[i][j].setSpeed(1);
		else
			c[i][j].setSpeed(temp + 1);
	}

	play->setXY(18, 19);
}

void CGAME::drawTruck()
{
	TextColor(10);
	for (int i = 0; i < n_Truck; i++)
	{
		for (int j = 0; j < MAX_TRUCK_LENGTH-1; j++)
		{
			if (stopm(t[i][j].Y()) == 0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			t[i][j].drawTruck();
		}
		TextColor(14);
	}
	TextColor(7);
}

void CGAME::drawCar()
{
		for (int i = MAX_CAR - 5; i < MAX_CAR; i++){
			for (int j = 0; j < MAX_CAR_LENGTH; j++){
				goToXY(c[i][j].X(), c[i][j].Y());
				cout << "     ";
			}
		}
		for (int i = 0; i<MAX_CAR - 5; i++){
			for (int j = 0; j<MAX_CAR_LENGTH ; j++){
				goToXY(c[i][j].X(), c[i][j].Y());
				cout << (char)219;
			}
			if (i % 2 == 1){
				goToXY(c[i][MAX_CAR_LENGTH - 1].X(), c[i][MAX_CAR_LENGTH - 1].Y());
				cout << (char)209;
			}
			else{
				goToXY(c[i][0].X(), c[i][0].Y());
				cout << (char)220;
			}
		}
}

void CGAME::drawBird()
{
	TextColor(10);
	for (int i = 0; i < n_Bird; i++)
	{
		for (int j = 0; j < MAX_BIRD_LENGTH - 1; j++)
		{
			if (stopm(b[i][j].Y()) == 0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			b[i][j].drawBird();
		}
		TextColor(14);
	}
	TextColor(7);
}


void CGAME::drawDinausor()
{
	TextColor(10);
	for (int i = 0; i < n_Dinausor; i++)
	{
		for (int j = 0; j < MAX_DINAUSOR_LENGTH - 1; j++)
		{
			if (stopm(d[i][j].Y()) == 0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			d[i][j].drawDinausor();
		}
		TextColor(14);
	}
	TextColor(7);
}
void CGAME::DrawBoard(int x, int y, int width, int height)
{
	goToXY(x, y);
	cout << "*";
	for (int i = 1; i < width; i++)cout << "*";
	cout << '*';
	goToXY(x, height + y);
	cout << '*';
	for (int i = 1; i < width; i++)cout << '*';
	cout << '*';
}
bool CGAME::isImpact(int z)
{
	if (z == 1 || z == 19) return 0;
	for (int i = 0; i < MAX_TRUCK_LENGTH; i++)
	if (z - 2 >= 0 && z - 2 < n_Truck)
	if (play->X() == t[z - 2][i].X() && play->Y() == t[z - 2][i].Y())
		return 1;
	for (int i = 0; i < MAX_CAR_LENGTH; i++)
	if (z - 2 >= 0 && z - 2 < n_Car)
	if (play->X() == c[z - 2][i].X() && play->Y() == c[z - 2][i].Y())
		return 1;
	return 0;
}

void CGAME::moveTruck()
{
	int cnt;
	if (STOP1%2==0)
	for (int i = 1; i < MAX_TRUCK; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = 0; j < MAX_TRUCK_LENGTH - 1; j++)
			if (stopm(t[i][j].Y()) == 1)
				t[i][j] = t[i][j + 1];
			if (stopm(t[i][MAX_TRUCK_LENGTH - 1].Y()) == 1)
			{
				int temp = t[i][MAX_TRUCK_LENGTH - 1].X() + 1;
				if (temp == WIDTH_CONSOLE)
					t[i][MAX_TRUCK_LENGTH - 1].setX(1);
				else
					t[i][MAX_TRUCK_LENGTH - 1].setX(temp);
			}
		} while (cnt < t[0][0].Speed());
	}
	for (int i = 0; i <MAX_TRUCK; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = MAX_TRUCK_LENGTH - 1; j > 0; j--)
			if (stopm(t[i][j].Y() == 1))
				t[i][j] = t[i][j - 1];
			if (stopm(t[i][0].Y()) == 1)
			{
				int temp = t[i][0].X() - 1;
				if (temp == 0)
					t[i][0].setX(WIDTH_CONSOLE-1);
				else
					t[i][0].setX(temp);
			}
		} while (cnt < t[0][0].Speed());
	}
}

void CGAME::moveCar()
{
	int cnt;
	if (STOP1%2==0)
	for (int i = 1; i < n_Car; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = 0; j < MAX_CAR_LENGTH - 1; j++)
			if (stopm(c[i][j].Y()) == 1)
				c[i][j] = c[i][j + 1];
			if (stopm(c[i][MAX_CAR_LENGTH - 1].Y()) == 1)
			{
				int temp = c[i][MAX_CAR_LENGTH - 1].X() + 1;
				if (temp ==WIDTH_CONSOLE)
					c[i][MAX_CAR_LENGTH - 1].setX(1);
				else
					c[i][MAX_CAR_LENGTH - 1].setX(temp);
			}
		} while (cnt < 1);
	}
	for (int i = 0; i < n_Car; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = MAX_CAR_LENGTH - 1; j > 0; j--)
			if (stopm(c[i][j].Y() == 1))
				c[i][j] = c[i][j - 1];
			if (stopm(c[i][0].Y()) == 1)
			{
				int temp = c[i][0].X() - 1;
				if (temp == 0)
					c[i][0].setX(79);
				else
					c[i][0].setX(temp);
			}
		} while (cnt < 1);
	}
}


void CGAME::moveBird()
{
	int cnt;
	if (STOP1 % 2 == 0)
	for (int i = 1; i < MAX_BIRD; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = 0; j < MAX_BIRD_LENGTH - 1; j++)
			if (stopm(b[i][j].Y()) == 1)
				b[i][j] = b[i][j + 1];
			if (stopm(b[i][MAX_BIRD_LENGTH - 1].Y()) == 1)
			{
				int temp = b[i][MAX_BIRD_LENGTH - 1].X() + 1;
				if (temp == WIDTH_CONSOLE)
					b[i][MAX_BIRD_LENGTH - 1].setX(1);
				else
					b[i][MAX_BIRD_LENGTH - 1].setX(temp);
			}
		} while (cnt < b[0][0].Speed());
	}
	for (int i = 0; i <MAX_BIRD; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = MAX_TRUCK_LENGTH - 1; j > 0; j--)
			if (stopm(b[i][j].Y() == 1))
				b[i][j] = b[i][j - 1];
			if (stopm(b[i][0].Y()) == 1)
			{
				int temp = b[i][0].X() - 1;
				if (temp == 0)
					b[i][0].setX(WIDTH_CONSOLE - 1);
				else
					b[i][0].setX(temp);
			}
		} while (cnt < b[0][0].Speed());
	}
}

void CGAME::moveDinausor()
{
	int cnt;
	if (STOP1 % 2 == 0)
	for (int i = 1; i < MAX_DINAUSOR; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = 0; j < MAX_DINAUSOR_LENGTH - 1; j++)
			if (stopm(d[i][j].Y()) == 1)
				d[i][j] = d[i][j + 1];
			if (stopm(d[i][MAX_DINAUSOR_LENGTH - 1].Y()) == 1)
			{
				int temp = d[i][MAX_DINAUSOR_LENGTH - 1].X() + 1;
				if (temp == WIDTH_CONSOLE)
					d[i][MAX_DINAUSOR_LENGTH - 1].setX(1);
				else
					d[i][MAX_DINAUSOR_LENGTH - 1].setX(temp);
			}
		} while (cnt < d[0][0].Speed());
	}
	for (int i = 0; i <MAX_DINAUSOR; i += 2)
	{
		cnt = 0;
		do
		{
			cnt++;
			for (int j = MAX_DINAUSOR_LENGTH - 1; j > 0; j--)
			if (stopm(d[i][j].Y() == 1))
				d[i][j] = d[i][j - 1];
			if (stopm(d[i][0].Y()) == 1)
			{
				int temp = d[i][0].X() - 1;
				if (temp == 0)
					d[i][0].setX(WIDTH_CONSOLE - 1);
				else
					d[i][0].setX(temp);
			}
		} while (cnt < d[0][0].Speed());
	}
}
void CGAME::eraseBird()
{
	int cnt;
	for (int i = 0; i < n_Bird; i += 2)
	{
		cnt = 0;
		do
		{
			int x = b[i][MAX_BIRD_LENGTH - 1 - cnt].X();
			int y = b[i][MAX_BIRD_LENGTH - 1 - cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < b[0][0].Speed());
	}
	for (int i = 1; i < n_Bird; i += 2)
	{
		cnt = 0;
		do
		{
			int x = b[i][cnt].X();
			int y = b[i][cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < b[0][0].Speed());
	}
}
void CGAME::eraseTruck()
{
	int cnt;
	for (int i = 0; i < n_Truck; i += 2)
	{
		cnt = 0;
		do
		{
			int x = t[i][MAX_TRUCK_LENGTH - 1 - cnt].X();
			int y = t[i][MAX_TRUCK_LENGTH - 1 - cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < t[0][0].Speed());
	}
	for (int i = 1; i < n_Truck; i += 2)
	{
		cnt = 0;
		do
		{
			int x = t[i][cnt].X();
			int y = t[i][cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < t[0][0].Speed());
	}
}

void CGAME::eraseCar()
{
	int cnt;
	for (int i = 0; i < n_Car; i += 2)
	{
		cnt = 0;
		do
		{
			int x = c[i][MAX_CAR_LENGTH - 1 - cnt].X();
			int y = c[i][MAX_CAR_LENGTH - 1 - cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < c[0][0].Speed());
	}
	for (int i = 1; i < n_Car; i += 2)
	{
		cnt = 0;
		do
		{
			int x = c[i][cnt].X();
			int y = c[i][cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < c[0][0].Speed());
	}

}
void CGAME::eraseDinausor()
{
	int cnt;
	for (int i = 0; i < n_Dinausor; i += 2)
	{
		cnt = 0;
		do
		{
			int x = d[i][MAX_DINAUSOR_LENGTH - 1 - cnt].X();
			int y = d[i][MAX_DINAUSOR_LENGTH - 1 - cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < d[0][0].Speed());
	}
	for (int i = 1; i < n_Dinausor; i += 2)
	{
		cnt = 0;
		do
		{
			int x = d[i][cnt].X();
			int y = d[i][cnt].Y();
			goToXY(x, y);
			cout << " ";
			cnt++;
		} while (cnt < d[0][0].Speed());
	}
}
bool CGAME::stopm(int i)
{
	if (play->Level() == 0)
		return 1;
	if (((time - beginTime) % 60000) < 60000 - (play->Level() + 1) * 10000)
		return 1;
	for (int j = play->Y() - play->Level(); j <= play->Y() + play->Level(); j++)
	if (i == j)
		return 0;
	return 1;
}

void CGAME::STOP()
{
	int flag = 1;
	goToXY(WIDTH_CONSOLE - 22, HEIGH_CONSOLE+1);
	char c1 = (char)219;
	rlutil::setColor(4);
	cout << c1;
	goToXY(WIDTH_CONSOLE - 22, HEIGH_CONSOLE + 3);
	char c2 = (char)219;
	rlutil::setColor(2);
	cout << c2;
	goToXY(WIDTH_CONSOLE - 22, HEIGH_CONSOLE +5);
	char c3 = (char)219;
	rlutil::setColor(6);
	cout << c3;
	int dem = 0;
	if (nStop1 == 6000)
	{
		nStop1 = 0;
		STOP1++;
	}
	else{
		nStop1 += 50;
		int i = STOP1 % 2 + 1;
		goToXY(WIDTH_CONSOLE-15, HEIGH_CONSOLE+3);
			if (nStop1 % 1000 > 200)
			{
				cout << "Time stop:" << 7 - nStop1 / 1000 - 2;
				if (nStop1 / 1000 == 4)
				{
					goToXY(WIDTH_CONSOLE - 22, HEIGH_CONSOLE+3);
					char c1 = (char)219;
					rlutil::setColor(4);
					cout << c1;
				}
			}
			else cout << " ";
		goToXY(play->X(), play->Y());
	}
	if (isImpact(play->Y()))
	{
		DrawLose();
		processDead();
	}
	if (play->Y() == 1)
	{
		int x1 = play->X();
		int y1 = play->Y();
		POINT Y;
		Y.x = x1;
		Y.y = y1;
		ProcessResult(Y);
		goToXY(WIDTH_CONSOLE-10, HEIGH_CONSOLE+1);
		cout << "Score:" << nRESULT1;
		processFinish();
	}
}