#pragma once

#include"GameFunc.h"
#include"Player.h"


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
	friend class MapInfo;
private:
	bool isDoor[4];
	list<Object*> objectList;
public:
	Room(bool isDoor[4], list<Object*>& objectList);
	Room();
	bool IsDoor(DIRECTION_TYPE dir);	//���ʿ� ���� �ִ���
	bool IsUse();	//���Ǵ� ������ Ȯ��
	~Room();
};

class GameManager
{
private:
	static GameManager* singleton;	//�ϳ��� �����ȴ�
	GameManager();					//�̱����̶� �����ڰ� private
	void PrintMap(int mapX,int mapY);	//�����
	void CreateDebugMap();				//����׿�ʻ���
	void CreateMap();
public:
	Room* map[9][9];				//������
	list<Object*>* nowObjectList;	//���� �� ������Ʈ����Ʈ
	Object* collisionTable[30][50];	//���� �� �浹 ���̺�
	list<string> message;			//�޼�������Ʈ
	int nowMapX, nowMapY;			//���� �� ��ǥ
	GAMESTATE_TYPE gameState;		//���� ���� ����
	Player * player;				//�÷��̾�

	static GameManager * GetInstance();	//���ӸŴ��� ��ü���
	void KeyEvent();			//Ű�Է�
	void DrawFrame();			//��ü �����ӱ׸���
	void DrawPausePage();		//�Ͻ����� ȭ�� ���
	void DrawStartPage();		//���� ���� ȭ�� ���
	void DrawGameOverPage();	//���� ���� ȭ�� ���
	void DrawChangeMap();		//�ʺ�ȯ�� ���̴� ȭ��
	void PrintPlayerState();	//�÷��̾� ���� ���
	void GameSetting();			//���� ������ �غ�
	void ObjectUpdate();		//nowObjectList�� Object���� Update()����
	void ObjectDraw();			//nowObjectList�� Object���� Draw()����
	void SetMessage(list<string>& newMessage);	//�޼��� ���� ��ħ
	void NextMessage();			//�޼�������Ʈ�� �������� ���
	DIRECTION_TYPE IsMapChange();	//�ʺ����Ȳ���� Ȯ��
	void ChangeMap(DIRECTION_TYPE dir);	//�ʺ���
	void SetGameState(GAMESTATE_TYPE state);	//���� ���� ����
	~GameManager();
};