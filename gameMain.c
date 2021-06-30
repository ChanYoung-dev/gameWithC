#include <conio.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#include "Digitalv.h"


#pragma comment(lib, "winmm.lib") 



#define ENTER 13
#define UP 72
#define RIGHT 77
#define DOWN 80
#define LEFT 75
#define line 15

void BufferClear()
{
	while (getchar() != '\n');
}
static void consoletitle()
{

	system("mode con:cols=200 lines=40");
	system("Title 포즈게임");
}
void removeCursor(void)  //커서 지우기
{
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

void gotoxy(int x, int y) // 커서 이동
{
	COORD pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcolor(int color) // 색깔입히기
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void resetcolor()  // 색깔초기화
{
	setcolor(7);
}
void who(int);
void loading(); // 로딩화면
int whofirst(int); // 선 정하기
void menu(); //메뉴
void cursormove(); //커서이동
void Initialize(void); // 오목판그리기
void Render(void); // 오목판 출력
void WHITEmove(void); //백돌 움직일때
void BLACKmove(void); //흑돌 움직일때
int Quiz(void); //퀴즈
int check(void); //승리체크 

char* OmokBoard[15][15]; // 오목판배열


int main()
{

	

	int cp; //currentplayer 현재플레이어가 누군지
	int n=1;
	mciSendString("play dance.mp3", NULL, 0, NULL);
	consoletitle(); 
	loading();
	system("cls");
	menu();
	while (1)
	{

		cp = whofirst(n); //주사위게임을 두명돌려서 선을 정함 이긴사람은 cp로 설정
		system("cls");
		
		
		Initialize(); //바둑판그리기
		who(cp); //cp에 따른 cp가 1이면 백돌,2면 흑돌옮기기함수
		while (1)
		{

			if (cp == 1)
				cp = 2;
			else
				cp = 1; //턴바뀜

			who(cp);
			if (1 == check()) //승리자가 생기면 다시하기
				break;
		}
		n++;
	}
	
}
	
	


void loading()
{

	int i, j;
	int count = 30;
	for (i = 0; i < count; ++i)
	{
		system("cls");
		gotoxy(55, 20);

		printf("게임 로딩중");
		for (j = 0; j < count; ++j)
		{
			if (j <= i)
			{
				printf("■");
			}
			else
			{
				printf("□");

			}

		}

	}

}
void menu()
{
	gotoxy(1, 15);
	printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★★☆★\n\n\n");
	printf("                                                                                                                                                                                             \n");
	printf("                                                                               G A M E S T A R T !                                                                                           \n");
	printf("                                                                                                                                                                                             \n");
	printf("                                                                                                                                                                                             \n");
	printf("                                                                               G A M E H E L P ?                                                                                             \n");
	printf("                                                                                                                                                                                             \n");
	printf("                                                                                                                                                                                             \n");
	printf("                                                                               E X I T                                                                                                 \n");
	printf("                                                                                                                                                                                         \n\n\n");
	printf("★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★★☆★☆★☆★\n");
	cursormove();
}
void cursormove()
{
	removeCursor();
	int insert;

	int x = 80, y = 19;
	int i = 1;

	while (!_kbhit()) {
		gotoxy(x, y);
		setcolor(rand() % 15 + 1);
		printf("G A M E S T A R T !");
	}
	resetcolor();
	while (i) {

		insert = _getch();
		switch (insert)
		{
		case ENTER:
			if (y == 19) {

				return 0;
				--i;

			}
			else if (y == 22) {
				printf("도움말");
				--i;
			}
			else if (y == 25) {
				exit(0);

			}
			break;
		case UP:


			PlaySound("music.wav", NULL, SND_ASYNC);

			
			if (y == 19)
				y = 25;
			else if (y == 22)
				y = 19;
			else if (y == 25)
				y = 22;
			gotoxy(x, y);

			if (y == 19) {
				gotoxy(x, y + 3);
				resetcolor();
				printf("G A M E H E L P ?");
				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);
					printf("G A M E S T A R T !");

				}
			}

			else if (y == 22) {
				gotoxy(x, y + 3);
				resetcolor();
				printf("E X I T");
				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);
					printf("G A M E H E L P ?");

				}
			}
			else if (y == 25) {
				gotoxy(x, y - 6);
				resetcolor();
				printf("G A M E S T A R T !");
				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);
					printf("E X I T");
				}
			}

			break;
		case DOWN:
			PlaySound("music.wav", NULL, SND_ASYNC);
			if (y == 19)
				y = 22;
			else if (y == 22)
				y = 25;
			else if (y == 25)
				y = 19;
			gotoxy(x, y);
			setcolor(4);
			if (y == 19) {
				gotoxy(x, y + 6);
				resetcolor();
				printf("E X I T");
				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);

					printf("G A M E S T A R T !");


					Sleep(50);
				}
			}

			else if (y == 22) {
				gotoxy(x, y - 3);
				resetcolor();
				printf("G A M E S T A R T !");

				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);
					printf("G A M E H E L P ?");
					Sleep(50);
				}
			}
			else if (y == 25) {
				gotoxy(x, y - 3);
				resetcolor();
				printf("G A M E H E L P ?");
				while (!_kbhit()) {
					gotoxy(x, y);
					setcolor(rand() % 6 + 1);
					printf("E X I T");
					Sleep(50);
				}
			}
			break;

		}
	}
}
int whofirst(int n)
{
	
	srand((unsigned)time(NULL));

	resetcolor();
	int cp;
	int p1number;
	int p2number=0;
	int num;
	
	
	while (!_kbhit()) {
		system("cls");
		gotoxy(60, 10);
		printf("원하는 타이밍에 ENTER를 눌러주세요.");
		gotoxy(40, 14);
		printf("PLAYER1");
		gotoxy(76, 20);
		printf("vs");
		gotoxy(80, 14);
		printf("PLAYER2");
		gotoxy(80, 15);
		printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
		printf("■                              ■\n"); gotoxy(80, 17);
		printf("■                              ■\n"); gotoxy(80, 18);
		printf("■                              ■\n"); gotoxy(80, 19);
		printf("■                              ■\n"); gotoxy(80, 20);
		printf("■                              ■\n"); gotoxy(80, 21);
		printf("■                              ■\n"); gotoxy(80, 22);
		printf("■                              ■\n"); gotoxy(80, 23);
		printf("■                              ■\n"); gotoxy(80, 24);
		printf("■                              ■\n"); gotoxy(80, 25);
		printf("■                              ■\n"); gotoxy(80, 26);
		printf("■                              ■\n"); gotoxy(80, 27);
		printf("■                              ■\n"); gotoxy(80, 28);
		printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);

		gotoxy(40, 15);
		p1number = rand() % 6 + 1;
		switch (p1number)
		{
		case 1:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■             ■               ■\n"); gotoxy(40, 18);
			printf("■           ■■               ■\n"); gotoxy(40, 19);
			printf("■             ■               ■\n"); gotoxy(40, 20);
			printf("■             ■               ■\n"); gotoxy(40, 21);
			printf("■             ■               ■\n"); gotoxy(40, 22);
			printf("■             ■               ■\n"); gotoxy(40, 23);
			printf("■             ■               ■\n"); gotoxy(40, 24);
			printf("■             ■               ■\n"); gotoxy(40, 25);
			printf("■             ■               ■\n"); gotoxy(40, 26);
			printf("■          ■■■■            ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;

		case 2:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■         ■■■■■           ■\n"); gotoxy(40, 18);
			printf("■                  ■          ■\n"); gotoxy(40, 19);
			printf("■                  ■          ■\n"); gotoxy(40, 20);
			printf("■                 ■           ■\n"); gotoxy(40, 21);
			printf("■               ■             ■\n"); gotoxy(40, 22);
			printf("■             ■               ■\n"); gotoxy(40, 23);
			printf("■           ■                 ■\n"); gotoxy(40, 24);
			printf("■          ■                  ■\n"); gotoxy(40, 25);
			printf("■         ■                   ■\n"); gotoxy(40, 26);
			printf("■         ■■■■■■         ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;
		case 3:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■         ■■■■■           ■\n"); gotoxy(40, 18);
			printf("■                  ■          ■\n"); gotoxy(40, 19);
			printf("■                   ■         ■\n"); gotoxy(40, 20);
			printf("■                  ■          ■\n"); gotoxy(40, 21);
			printf("■            ■■■            ■\n"); gotoxy(40, 22);
			printf("■                 ■           ■\n"); gotoxy(40, 23);
			printf("■                  ■          ■\n"); gotoxy(40, 24);
			printf("■                   ■         ■\n"); gotoxy(40, 25);
			printf("■                  ■          ■\n"); gotoxy(40, 26);
			printf("■         ■■■■■           ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;
		case 4:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■              ■              ■\n"); gotoxy(40, 18);
			printf("■             ■               ■\n"); gotoxy(40, 19);
			printf("■            ■                ■\n"); gotoxy(40, 20);
			printf("■           ■                 ■\n"); gotoxy(40, 21);
			printf("■          ■    ■            ■\n"); gotoxy(40, 22);
			printf("■         ■     ■            ■\n"); gotoxy(40, 23);
			printf("■        ■■■■■■■        ■\n"); gotoxy(40, 24);
			printf("■                ■            ■\n"); gotoxy(40, 25);
			printf("■                ■            ■\n"); gotoxy(40, 26);
			printf("■                ■            ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;
		case 5:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■          ■■■■■          ■\n"); gotoxy(40, 18);
			printf("■          ■                  ■\n"); gotoxy(40, 19);
			printf("■          ■                  ■\n"); gotoxy(40, 20);
			printf("■          ■■■■            ■\n"); gotoxy(40, 21);
			printf("■                 ■           ■\n"); gotoxy(40, 22);
			printf("■                   ■         ■\n"); gotoxy(40, 23);
			printf("■                    ■        ■\n"); gotoxy(40, 24);
			printf("■                   ■         ■\n"); gotoxy(40, 25);
			printf("■                  ■          ■\n"); gotoxy(40, 26);
			printf("■          ■■■■            ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;
		case 6:
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 16);
			printf("■                              ■\n"); gotoxy(40, 17);
			printf("■               ■             ■\n"); gotoxy(40, 18);
			printf("■              ■              ■\n"); gotoxy(40, 19);
			printf("■             ■               ■\n"); gotoxy(40, 20);
			printf("■            ■                ■\n"); gotoxy(40, 21);
			printf("■           ■                 ■\n"); gotoxy(40, 22);
			printf("■          ■  ■■            ■\n"); gotoxy(40, 23);
			printf("■         ■       ■          ■\n"); gotoxy(40, 24);
			printf("■         ■        ■         ■\n"); gotoxy(40, 25);
			printf("■          ■      ■          ■\n"); gotoxy(40, 26);
			printf("■            ■■■            ■\n"); gotoxy(40, 27);
			printf("■                              ■\n"); gotoxy(40, 28); 
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(40, 29);
			break;
		}
		Sleep(100);
	}
	if (n != 1) {
		getchar();
	}
	BufferClear();
	while (!_kbhit()) {
		gotoxy(80, 14);
		printf("PLAYER2");
		

		

		gotoxy(80,15 );
		p2number = rand() % 6 + 1;
		switch (p2number)
		{
		case 1:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■             ■               ■\n"); gotoxy(80, 18);
			printf("■           ■■               ■\n"); gotoxy(80, 19);
			printf("■             ■               ■\n"); gotoxy(80, 20);
			printf("■             ■               ■\n"); gotoxy(80, 21);
			printf("■             ■               ■\n"); gotoxy(80, 22);
			printf("■             ■               ■\n"); gotoxy(80, 23);
			printf("■             ■               ■\n"); gotoxy(80, 24);
			printf("■             ■               ■\n"); gotoxy(80, 25);
			printf("■             ■               ■\n"); gotoxy(80, 26);
			printf("■          ■■■■            ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;

		case 2:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■         ■■■■■           ■\n"); gotoxy(80, 18);
			printf("■                  ■          ■\n"); gotoxy(80, 19);
			printf("■                  ■          ■\n"); gotoxy(80, 20);
			printf("■                 ■           ■\n"); gotoxy(80, 21);
			printf("■               ■             ■\n"); gotoxy(80, 22);
			printf("■             ■               ■\n"); gotoxy(80, 23);
			printf("■           ■                 ■\n"); gotoxy(80, 24);
			printf("■          ■                  ■\n"); gotoxy(80, 25);
			printf("■         ■                   ■\n"); gotoxy(80, 26);
			printf("■         ■■■■■■         ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;
		case 3:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■         ■■■■■           ■\n"); gotoxy(80, 18);
			printf("■                  ■          ■\n"); gotoxy(80, 19);
			printf("■                   ■         ■\n"); gotoxy(80, 20);
			printf("■                  ■          ■\n"); gotoxy(80, 21);
			printf("■            ■■■            ■\n"); gotoxy(80, 22);
			printf("■                 ■           ■\n"); gotoxy(80, 23);
			printf("■                  ■          ■\n"); gotoxy(80, 24);
			printf("■                   ■         ■\n"); gotoxy(80, 25);
			printf("■                  ■          ■\n"); gotoxy(80, 26);
			printf("■         ■■■■■           ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;
		case 4:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■              ■              ■\n"); gotoxy(80, 18);
			printf("■             ■               ■\n"); gotoxy(80, 19);
			printf("■            ■                ■\n"); gotoxy(80, 20);
			printf("■           ■                 ■\n"); gotoxy(80, 21);
			printf("■          ■    ■            ■\n"); gotoxy(80, 22);
			printf("■         ■     ■            ■\n"); gotoxy(80, 23);
			printf("■        ■■■■■■■        ■\n"); gotoxy(80, 24);
			printf("■                ■            ■\n"); gotoxy(80, 25);
			printf("■                ■            ■\n"); gotoxy(80, 26);
			printf("■                ■            ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;
		case 5:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■          ■■■■■          ■\n"); gotoxy(80, 18);
			printf("■          ■                  ■\n"); gotoxy(80, 19);
			printf("■          ■                  ■\n"); gotoxy(80, 20);
			printf("■          ■■■■            ■\n"); gotoxy(80, 21);
			printf("■                 ■           ■\n"); gotoxy(80, 22);
			printf("■                   ■         ■\n"); gotoxy(80, 23);
			printf("■                    ■        ■\n"); gotoxy(80, 24);
			printf("■                   ■         ■\n"); gotoxy(80, 25);
			printf("■                  ■          ■\n"); gotoxy(80, 26);
			printf("■          ■■■■            ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;
		case 6:
			if (p1number == p2number)
				break;
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 16);
			printf("■                              ■\n"); gotoxy(80, 17);
			printf("■               ■             ■\n"); gotoxy(80, 18);
			printf("■              ■              ■\n"); gotoxy(80, 19);
			printf("■             ■               ■\n"); gotoxy(80, 20);
			printf("■            ■                ■\n"); gotoxy(80, 21);
			printf("■           ■                 ■\n"); gotoxy(80, 22);
			printf("■          ■  ■■            ■\n"); gotoxy(80, 23);
			printf("■         ■       ■          ■\n"); gotoxy(80, 24);
			printf("■         ■        ■         ■\n"); gotoxy(80, 25);
			printf("■          ■      ■          ■\n"); gotoxy(80, 26);
			printf("■            ■■■            ■\n"); gotoxy(80, 27);
			printf("■                              ■\n"); gotoxy(80, 28);
			printf("■■■■■■■■■■■■■■■■■\n"); gotoxy(80, 29);
			break;
		}
		Sleep(100);

	}
	
	
	
	
		if (p2number > p1number) {
			gotoxy(60, 10);
			printf("          ");
			gotoxy(70, 10);
			printf("p2가 선입니다.           \n");
			

			cp = 2;

		}
		else if (p1number > p2number) {
			gotoxy(60, 10);
			printf("          ");
			printf("p1가 선입니다.           \n");
			
			cp = 1;

		}
		else {
			printf("오류!"); return 0;
		}
		for (num = 5; num >-1;num--) {
			gotoxy(70, 11);
			printf("%d초 뒤 게임이 시작됩니다.", num);
			Sleep(1000);
		}
		
	
		return cp;
}


typedef struct Problem

{

	char what[100];

	char correct[100];

}Problem;



void Initialize(void)
{
	
	
	int i, j;
	for (i = 0; i<line; ++i)
	{
		for (j = 0; j<line; ++j)
		{
			if (0 == i)
			{
				if (0 == j)
				{
					OmokBoard[i][j] = "┌";
				}
				else if (line - 1 == j)
				{
					OmokBoard[i][j] = "┐";
				}
				else
				{
					OmokBoard[i][j] = "─";
				}
			}
			else if (line - 1 == i)
			{
				if (0 == j)
				{
					OmokBoard[i][j] = "└";
				}
				else if (line - 1 == j)
				{
					OmokBoard[i][j] = "┘";
				}
				else
				{
					OmokBoard[i][j] = "─";
				}
			}
			else if (1 == i % 2)
			{
				if (1 == j % 2)
				{
					OmokBoard[i][j] = "　";
				}
				else if (0 == j % 2)
				{
					OmokBoard[i][j] = "│";
				}
			}
			else if (0 == i % 2)
			{
				if (0 == j)
				{
					OmokBoard[i][j] = "├";
				}
				else if (line - 1 == j)
				{
					OmokBoard[i][j] = "┤";
				}
				else if (1 == j % 2)
				{
					OmokBoard[i][j] = "─";
				}
				else if (0 == j % 2)
				{
					OmokBoard[i][j] = "┼";
				}
			}
		}
	}
	Render();
	gotoxy(32, 8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(32, 9);
	printf("■                                                                      ■\n");
	gotoxy(32, 10);
	printf("■                                                                      ■\n");
	gotoxy(32, 11);
	printf("■                                                                      ■\n");
	gotoxy(32, 12);
	printf("■                                                                      ■\n");
	gotoxy(32, 13);
	printf("■                                                                      ■\n");
	gotoxy(32, 14);
	printf("■                                                                      ■\n");
	gotoxy(32, 15);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

}
void who(int cp) {
	if (cp == 1)
		WHITEmove();
	else
		BLACKmove();
}
void Render(void)
{
	int num = 16;
	gotoxy(55, 16);
	int i, j;
	for (i = 0; i<line; ++i)
	{
		for (j = 0; j<line; ++j)
		{
			printf("%s", OmokBoard[i][j]);
		}
		
		printf("\n");
		num++;
		gotoxy(55, num);
	}
	printf("\n");
}

void BLACKmove(void)
{
	int x;
	getchar();
	fflush(stdin);

	
	int insert;
	int m = 1;
	int i = 0;
	int j = 0;
	gotoxy(60, 11);
	printf("PLAYER2(●) 차례입니다.                     ");
	gotoxy(60, 12);
	printf("방향키를 눌러주세요.                      ");
	
	gotoxy(i * 4 + 57, j * 2 + 17);
	printf("▒");
	while (1) {
		insert = _getch();
		switch (insert)
		{
		case RIGHT:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (i == 6) {
				i = 0;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			i += 1;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case LEFT:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (i == 0) {
				i = 6;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			i -= 1;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			
			break;
		case UP:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (j == 0) {
				j = 6;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			j--;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case DOWN:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1&&OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (j == 6) {
				j = 0;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			j++;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case ENTER:
			
			if (Quiz() == 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
				Sleep(1500);
			}
			else {
				gotoxy(i * 4 + 57, j * 2 + 17);
				OmokBoard[2 * i + 1][2 * j + 1] = 2;
				printf("●");
				Sleep(1500);
			}
				
			
			

			
			return 0;
		
		}

	}


}
void WHITEmove(void)
{
	int x;
	getchar();
	fflush(stdin);
	int insert;
	int m = 1;
	int i = 0;
	int j = 0;
	gotoxy(60, 11);
	printf("PLAYER1(○) 차례입니다.                    ");
	gotoxy(60, 12);
	printf("방향키를 눌러주세요.                    ");
	
	gotoxy(i * 4 + 57, j * 2 + 17);
	printf("▒");
	while (1) {
		insert = _getch();
		switch (insert)
		{
		case RIGHT:

			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (i == 6) {
				i = 0;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			i += 1;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case LEFT:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (i == 0) {
				i = 6;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			i -= 1;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case UP:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (j == 0) {
				j = 6;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			j--;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case DOWN:
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
			}
			if (j == 6) {
				j = 0;
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("▒");
				break;
			}

			j++;
			gotoxy(i * 4 + 57, j * 2 + 17);
			if (OmokBoard[2 * i + 1][2 * j + 1] != 1 && OmokBoard[2 * i + 1][2 * j + 1] != 2) {
				printf("▒");
			}
			break;
		case ENTER:
			
			if (Quiz() == 2)
			{
				gotoxy(i * 4 + 57, j * 2 + 17);
				printf("　");
				Sleep(1000);
			}
			else {
				gotoxy(i * 4 + 57, j * 2 + 17);
				OmokBoard[2 * i + 1][2 * j + 1] = 1;
				printf("○");
				Sleep(1000);
			}
			return 0;
		}

	}


}

int Quiz(void)
{
	
	int number;
	int timeing=1;
	int i = 0;
	double pst;
	time_t start, end;
	int timing=0;
	Problem pros[100] =

	{

		{ "모래사장에 살고 있는 마녀를 뭐라고 할까요?(영어로)", "sandwich" },

		{ "대한민국을 영어로 하면(대문자로)?", "KOREA" },
		 
	    { "올라가기만하고, 내려오지 않는 것은 (알파벳)?", "age" },
	
		{ "수박속에 든 것은 (알파벳)?", "c" },

		{ "모기의 밥은 (알파벳)?", "p" },

		{ "닭이 낳는 것은 (알파벳)?", "r" },

		{ "몸에 들어가면 가려운 것은 (알파벳)?", "e" },

		{ "영화,광고 등에 특정제품 소품을 배경으로 집어넣는 마케팅 기법은?", "ppl" },

		{ "미국 하버드생 마크 주커가 개발한 소셜네트워크 서비스는?", "facebook" },

		{ "한국과 북한 사이에 있는 비무장지대를 약칭하는 이 용어는(대문자로)?", "DMZ" },

		{ "경쟁이 치열해진 산업을 일컫는 말로 blue ocean의 반대말은?", "red ocean" },

		{ "세계적인 무료 동영상 공유 사이트는?", "youtube" },

		{"겉은 바삭하고 속은 부드러운 막대기 모양으로 프랑스어로 지팡이라는 뜻의 빵은 ?", "baguette" },

		{ "전쟁의 피해로 고통받는 어린이,청소년을 구호하기 위한 목적으로 설립된 UN산하 기구는", "unicef" },

		
		

	};

	Problem *problem;
	

	int question;
	char answer[50]="";
	
	gotoxy(60, 12);
	printf("                       ");
	gotoxy(55, 11);
	printf("문제번호를 선택하십시오(1~1000):");
	scanf_s("%d", &number);
	
	gotoxy(55, 11);
	printf("문제:%s \n", pros[number].what);
	
	start = time(NULL);
	while (1)
	{
		end = time(NULL);
		pst = difftime(end, start);
		if (pst >= 8)
		{
			printf("시간 초과");
			gotoxy(60, 5);
			printf("         ");
			break;
		}
		if (pst > timeing)

		{
			setcolor(12);
			
			gotoxy(65, 9);
			printf("%d 초 지남\n", timeing);
			timeing++;
			resetcolor();
		}
		gotoxy(60, 12);
		printf("답:");
		if (kbhit())
		{
			answer[i] = getche();
			if (answer[i] == 13)
			{
				answer[i] = '\0';
				break;
			}
			else if (answer[i] == 8)
			{
				answer[i - 1] = ' ';
				i = i - 2;

			}
			gotoxy(60, 12);
			printf("답:%s", answer);
			i++;
		}

	}
	if (!strcmp(pros[number].correct, answer)) {
		gotoxy(55, 11);
		printf("                                       ");
		gotoxy(60, 12);
		printf("     ");
		gotoxy(65, 12);
		printf("정답입니다!!   ");
		gotoxy(65, 9);
		printf("                ");

		return 1;
		
	}
	else {
		gotoxy(55, 11);
		printf("                                        ");
		gotoxy(60, 12);
		printf("     ");
		gotoxy(65, 12);
		printf("틀렸습니다!!   ");
		gotoxy(65, 9);
		printf("                ");

		return 2;
		

	}

}
int check(void)
{
	char re;
	int insert;
	int x=60, y=12;
	int i;
	int j;
	int p1win = 0;
	int p2win = 0;
	for (j = 0; j < (line - 1) / 2; j++) // |자 승리
	{
		for (i = 0; i < (line - 1) / 2; i++)
		{
			if (OmokBoard[2 * i + 1][2 * j + 1] == 1
				&& OmokBoard[2 * (i + 1) + 1][2 * j + 1] == 1
				&& OmokBoard[2 * (i + 2) + 1][2 * j + 1] == 1
				&& OmokBoard[2 * (i + 3) + 1][2 * j + 1] == 1)p1win = 1;
			else if (OmokBoard[2 * i + 1][2 * j + 1] == 2
				&& OmokBoard[2 * (i + 1) + 1][2 * j + 1] == 2
				&& OmokBoard[2 * (i + 2) + 1][2 * j + 1] == 2
				&& OmokBoard[2 * (i + 3) + 1][2 * j + 1] == 2)p2win = 1;
		}
	}
	for (i = 0; i < (line - 1) / 2; i++)//-
	{
		for (j = 0; j < (line - 1) / 2; j++)
		{
			if (OmokBoard[2 * i + 1][2 * j + 1] == 1
				&& OmokBoard[2 * i + 1][2 * (j+1) + 1] == 1
				&& OmokBoard[2 * i + 1][2 * (j +2)+ 1] == 1
				&& OmokBoard[2 * i + 1][2 * (j+3) + 1] == 1)p1win = 1;
			else if (OmokBoard[2 * i + 1][2 * j + 1] == 2
				&& OmokBoard[2 * i + 1][2 * (j+1) + 1] == 2
				&& OmokBoard[2 * i + 1][2 * (j+2) + 1] == 2
				&& OmokBoard[2 * i + 1][2 * (j+3) + 1] == 2)p2win = 1;
		}
	}
	for (j = 0; j < (line - 1) / 2; j++)
	{
		for (i = 0; i < (line - 1) / 2; i++)
		{
			if (OmokBoard[2 * i + 1][2 * j + 1] == 1
				&& OmokBoard[2 * (i+1) + 1][2 * (j + 1) + 1] == 1
				&& OmokBoard[2 * (i+2) + 1][2 * (j + 2) + 1] == 1
				&& OmokBoard[2 * (i+3) + 1][2 * (j + 3) + 1] == 1)p1win = 1;
			else if (OmokBoard[2 * i + 1][2 * j + 1] == 2
				&& OmokBoard[2 * (i+1) + 1][2 * (j + 1) + 1] == 2
				&& OmokBoard[2 * (i+2) + 1][2 * (j + 2) + 1] == 2
				&& OmokBoard[2 * (i+3) + 1][2 * (j + 3) + 1] == 2)p2win = 1;
		}
	}
	for (j = 0; j < (line - 1) / 2; j++)//-
	{
		for (i = 4; i < (line - 1) / 2; i++)
		{
			if (OmokBoard[2 * i + 1][2 * j + 1] == 1
				&& OmokBoard[2 * (i-1) + 1][2 * (j + 1) + 1] == 1
				&& OmokBoard[2 * (i-2) + 1][2 * (j + 2) + 1] == 1
				&& OmokBoard[2 * (i-3) + 1][2 * (j + 3) + 1] == 1)p1win = 1;
			else if (OmokBoard[2 * i + 1][2 * j + 1] == 2
				&& OmokBoard[2 * (i-1) + 1][2 * (j + 1) + 1] == 2
				&& OmokBoard[2 * (i-2) + 1][2 * (j + 2) + 1] == 2
				&& OmokBoard[2 * (i-3) + 1][2 * (j + 3) + 1] == 2)p2win = 1;
		}
	}
	if (p1win == 1||p2win==1)
	{
		gotoxy(60, 11);
		if (p1win == 1) {
			printf("player1(○) 승리입니다.");
		}
		else if (p2win == 1) {
			printf("player2(●) 승리입니다.");
		}
		
		gotoxy(60,12);
		printf("다시 하기       나가기");
		while (!_kbhit()) {
			gotoxy(x, y);
			setcolor(rand() % 15 + 1);
			printf("다시하기");
		}
		resetcolor();
		while (i) {

			insert = _getch();
			switch (insert)
			{
			case ENTER:
				if (x == 60)
				{
					return 1;
				}
				else if (x = 76)
				{
					exit(0);
				}
			case RIGHT:
				if (x == 60)
					x = 76;
				else if (x == 76)
					x = 60;
				gotoxy(x, y);
				if (x == 76) {
					gotoxy(60, 12);
					resetcolor();
					printf("다시하기");
					while (!_kbhit()) {
						gotoxy(x, y);
						setcolor(rand() % 6 + 1);
						printf("나가기");

					}
				}
				else if (x == 60)
				{
					gotoxy(76, 12);
					resetcolor();
					printf("나가기");
					while (!_kbhit()) {
						gotoxy(x, y);
						setcolor(rand() % 6 + 1);
						printf("다시하기");
					}
				}
				break;
			case LEFT:
				if (x == 60)
					x = 76;
				else if (x == 76)
					x = 60;
				gotoxy(x, y);
				if (x == 76) {
					gotoxy(60, 12);
					resetcolor();
					printf("다시하기");
					while (!_kbhit()) {
						gotoxy(x, y);
						setcolor(rand() % 6 + 1);
						printf("나가기");

					}
				}
				else if (x == 60)
				{
					gotoxy(76, 12);
					resetcolor();
					printf("나가기");
					while (!_kbhit()) {
						gotoxy(x, y);
						setcolor(rand() % 6 + 1);
						printf("다시하기");
					}
				}
				break;
			
				
						

			}
		}

		
		

	}
}
