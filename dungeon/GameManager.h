#pragma once

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include<list>
#include"mapinfo.h"
#include "Object.h"

using namespace std;

#define randomize() srand((unsigned)time(NULL))	//��ũ�� �Լ�
#define random(n) (rand() % (n))

#define FRAME 100	//�̷����� �����Ӽ�
#define FPS 60		//���� ���ư��� �����Ӽ� (���谪)

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;	//Ŀ��Ÿ������
typedef enum { UP, DOWN, LEFT, RIGHT } DIRECTION_TYPE;				//����Ÿ��
typedef enum { STARTMENU, GAMING, PAUSE, GAMEOVER } GAMESTATE_TYPE;	//���ӻ���Ÿ��

class gameview
{
	int sx, sy;
	int width, height;
};
class stateview
{

};

class massageview
{

};

class Room
{
	bool isDoor[4];
	list<Object> objcetList;
};

void setcursortype(CURSOR_TYPE c);		//Ŀ�� ��� �����Լ�
void gotoxy(int x, int y);				//(������,�Ʒ���)
void SetColor(int color, int bgcolor);	//�� �����Լ�


//==========================================��Ž ����
void DrawFrame();			//�����ӱ׸���