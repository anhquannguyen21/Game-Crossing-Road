#include"Game.h"
#include<MMsystem.h>
CGAME *cg=new CGAME();
CPEOPLE *pl = cg->getPlayer();
int MOVING;
void BackgroundMusic()
{
	PlaySound(TEXT("HipHopPolice.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}
void subThread()
{
	while (1)
	{
		if (pl->State()==1)
		{
			if (MOVING == 'W')
				cg->up();
			if (MOVING == 'A')
				cg->left();
			if (MOVING == 'D')
				cg->right();
			if (MOVING == 'S')
				cg->down();
			MOVING = ' ';
		
			cg->eraseTruck();
			cg->eraseCar();
			cg->moveTruck();
			cg->moveCar();
			cg->drawTruck();
			cg->drawCar();
			Sleep(70);
			cg->STOP();
		}
	}
}

void Menu()
{
	FILE*f;
	fopen_s(&f, "start.txt", "r");
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
	goToXY(5, HEIGH_CONSOLE + 5);
	cout << "(Y)Startgame" << endl;
	goToXY(5, HEIGH_CONSOLE + 6);
	cout << "(T)Loadgame" << endl;
	goToXY(5, HEIGH_CONSOLE + 7);
	cout << "(E)exit" << endl;
	int temp;
	{
		temp = toupper(_getch());
		switch (temp)
		{
		case'Y':cg->startGame(); break;
		case'T':
			char s[20];
			system("cls");
			goToXY(8, 8);
			cout << "Enterthefilename:";
			cin.getline(s, 20);
			if (cg->LoadData(s));
			else{
				cout << "EROR404!!";
				exit(0);
			}
			break;
		case'E':exit(0); break;
		default:cg->startGame(); break;
		}
	}
	return;
}


int main()

{
	int temp;
	fixConsoleWindow();
	BackgroundMusic();
	srand(time(NULL));
	Menu();
	thread t1(subThread);
	while (1)
	{
		temp = toupper(_getch());
		if (pl->State()== 1)
		{
			if (temp == 27)
			{
				t1.detach();
				cg->exitGame(t1.native_handle());
				return 0;
			}
			else if (temp == 'P'){
				cg->pauseGame(t1.native_handle());
			}
			else if (temp == 'T'){
				pl->State() == 0;
				cg->pauseGame(t1.native_handle());
				system("cls");
				goToXY(8, 8);
				char s[20];
				cout << "Enterthefilename:";
				cin.getline(s, 20);
				if (cg->LoadData(s))
					ResumeThread((HANDLE)t1.native_handle());
				else
				{
					cout << "eror"; exit(0);
				}
			}
			else if (temp == 'L'){
				pl->setState(0);
				system("cls");
				cg->SaveGames();
				t1.detach();
				TerminateThread(t1.native_handle(), 0);
				return 0;
			}
			else{
				ResumeThread((HANDLE)t1.native_handle());
				if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')

					MOVING = temp;
			}
		}
		else
		{
			if (temp == 'Y')cg->startGame();
			else{
				t1.detach();
				cg->exitGame(t1.native_handle());
				return 0;
			}
		}
	}
	return 0;
}

