#pragma once

#include<windows.h>
#include<time.h>
#include<iostream>
#include<list>
#include"mapinfo.h"
#include"Object.h"

using namespace std;

#define randomize() srand((unsigned)time(NULL))	//��ũ�� �Լ�
#define random(n) (rand() % (n))

#define FRAME 100	//�̷����� �����Ӽ�
#define FPS 60		//���� ���ư��� �����Ӽ� (���谪)

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;	//Ŀ��Ÿ������
typedef enum { UP, DOWN, LEFT, RIGHT } DIRECTION_TYPE;				//����Ÿ��
typedef enum { STARTMENU, GAMING, PAUSE, GAMEOVER } GAMESTATE_TYPE;	//���ӻ���Ÿ��

void setcursortype(CURSOR_TYPE c);		//Ŀ�� ��� �����Լ�
void gotoxy(int x, int y);				//(������,�Ʒ���)
void SetColor(int color, int bgcolor);	//�� �����Լ�


//==========================================��Ž ����

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
	friend class GameManager;
private:
	bool isDoor[4];
	list<Object*> objcetList;

public:
	Room(bool isDoor[4], list<Object*>& objectList);
	Room();
	~Room();
};

class GameManager
{
private:
	static GameManager* singleton;	//�ϳ��� �����ȴ�
	GameManager();					//�̱����̶� �����ڰ� private
	void PrintMap(int mapX,int mapY);	//�����
	void CreateMap();				//�ʻ���
public:
	Room* map[9][9];				//������
	list<Object*>* nowObjectList;	//���� �� ������Ʈ����Ʈ
	Object* collisionTable[30][50];	//���� �� �浹 ���̺�
	int nowMapX, nowMapY;			//���� �� ��ǥ
	GAMESTATE_TYPE gameState;		//���� ���� ����

	static GameManager * GetInstance();	//���ӸŴ��� ��ü���
	void DrawFrame();			//��ü �����ӱ׸���
	void DrawPausePage();		//�Ͻ����� ȭ�� ���
	void DrawStartPage();		//���� ���� ȭ�� ���
	void DrawGameOverPage();	//���� ���� ȭ�� ���
	void GameSetting();			//���� ������ �غ�
	void ObjectUpdate();		//nowObjectList�� Object���� Update()����
	void ObjectDraw();			//nowObjectList�� Object���� Draw()����
	void ChangeMap(DIRECTION_TYPE dir);	//�ʺ���
	~GameManager(); 
};