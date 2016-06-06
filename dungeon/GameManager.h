#pragma once

#include"GameFunc.h"
#include"Object.h"

using namespace std;




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
	Object * player;				//�÷��̾�

	static GameManager * GetInstance();	//���ӸŴ��� ��ü���
	void DrawFrame();			//��ü �����ӱ׸���
	void DrawPausePage();		//�Ͻ����� ȭ�� ���
	void DrawStartPage();		//���� ���� ȭ�� ���
	void DrawGameOverPage();	//���� ���� ȭ�� ���
	void GameSetting();			//���� ������ �غ�
	void ObjectUpdate();		//nowObjectList�� Object���� Update()����
	void ObjectDraw();			//nowObjectList�� Object���� Draw()����
	void ChangeMap(DIRECTION_TYPE dir);	//�ʺ���
	void SetGameState(GAMESTATE_TYPE state);	//���� ���� ����
	~GameManager();
};