#pragma once

#include<windows.h>
#include<time.h>
#include<iostream>
#include<list>
#include<string>
#include<math.h>

#define randomize() srand((unsigned)time(NULL))	//��ũ�� �Լ�
#define random(n) (rand() % (n))

#define FRAME 100	//�̷����� �����Ӽ�
#define FPS 60		//���� ���ư��� �����Ӽ� (���谪)

static const double PI = 3.141592;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;	//Ŀ��Ÿ������
typedef enum { UP, DOWN, LEFT, RIGHT, NONE } DIRECTION_TYPE;		 //����Ÿ��
typedef enum { STARTMENU, GAMING, PAUSE, GAMEOVER, GAMECLEAR } GAMESTATE_TYPE;	//���ӻ���Ÿ��

void setcursortype(CURSOR_TYPE c);		//Ŀ�� ��� �����Լ�
void gotoxy(int x, int y);				//(������,�Ʒ���)
void SetColor(int color, int bgcolor);	//�� �����Լ�
