#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
#include "ReadMapInfo.h"
//#include<algorithm>
//��Ŭ��带 �� ������ҵ�
using namespace std;

Room::Room(bool isDoor[4], list<Object*>& objectList)
{
	for (int i = 0; i < 4; i++)	//���� ��� ä����
		this->isDoor[i] = isDoor[i];
	this->objectList.assign(objectList.begin(), objectList.end());	//����Ʈ�� ����
}
Room::Room()
{
	for (int i = 0; i < 4; i++)	//���� ��� ����
		this->isDoor[i] = false;
	this->objectList.clear();	//����Ʈ �����
}
bool Room::IsDoor(DIRECTION_TYPE dir)
{
	return this->isDoor[dir];
}
bool Room::IsUse()
{
	return this->isDoor[UP] || this->isDoor[DOWN] || this->isDoor[LEFT] || this->isDoor[RIGHT];
}

GameManager::GameManager()
{
	this->gameState = STARTMENU;
	//�׳� �ִ´�.
}
void GameManager::PrintMap(int mapX, int mapY)
{	
	//�����
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (this->map[y][x]->isDoor[0] || this->map[y][x]->isDoor[1] || this->map[y][x]->isDoor[2] || this->map[y][x]->isDoor[3])
			{
				//�׸��� ��ġ
				int drawX = mapX + x * 8;
				int drawY = mapY + y * 4;
				//�� �׸���
				gotoxy(drawX, drawY);
				cout << "����";
				gotoxy(drawX, drawY + 1);
				cout << "��";
				gotoxy(drawX + 4, drawY + 1);
				cout << "��";
				gotoxy(drawX, drawY + 2);
				cout << "����";
				//��� �׸���
				if (this->map[y][x]->isDoor[UP])
				{
					gotoxy(drawX + 2, drawY - 1);
					cout << "��";
				}
				if (this->map[y][x]->isDoor[DOWN])
				{
					gotoxy(drawX + 2, drawY + 3);
					cout << "��";
				}
				if (this->map[y][x]->isDoor[LEFT])
				{
					gotoxy(drawX - 2, drawY + 1);
					cout << "��";
				}
				if (this->map[y][x]->isDoor[RIGHT])
				{
					gotoxy(drawX + 6, drawY + 1);
					cout << "��";
				}
			}
		}
	}
}
void GameManager::CreateDebugMap()		//���� �̿ϼ�
{
	//���� ��°�� ����...
	for (int y = 0; y < 9; y++) 
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();

	map[4][4]->isDoor[UP] = true;
	map[3][4]->isDoor[DOWN] = true;
	//for (int i = 0; i < 20; i++)
	//	map[4][4]->objectList.push_front(new EnemyB(i, 28));
	map[4][4]->objectList.push_back(new EnemyA(0, 2));
	map[4][4]->objectList.push_back(new EnemyA(3, 2));
	map[4][4]->objectList.push_back(new EnemyA(6  , 2));
	map[4][4]->objectList.push_back(new EnemyB(2, 2));
	map[4][4]->objectList.push_back(new EnemyB(44, 2));
	map[4][4]->objectList.push_back(new EnemyB(4, 2));
	map[4][4]->objectList.push_back(new EnemyB(40, 2));
	map[4][4]->objectList.push_back(new EnemyB(6, 23));
	map[4][4]->objectList.push_back(new EnemyB(40, 23));

	map[3][4]->objectList.push_back(new EnemyD(12, 3));
	map[3][4]->objectList.push_back(new EnemyC(22, 22));
	map[3][4]->objectList.push_back(new EnemyE(40, 22));
	map[3][4]->objectList.push_back(new EnemyD(13, 3));
	map[3][4]->objectList.push_back(new EnemyC(23, 22));
	map[3][4]->objectList.push_back(new EnemyE(43, 22));

}
void GameManager::CreateMap()
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();
	//�ʺ�켱
	list<int> nextMake;	//������ ������� �� ��ȣ
	nextMake.push_front(40);
	list<int>::iterator nowMake = nextMake.begin();
	for (int index = 0; nowMake != nextMake.end(); nowMake++, index++)
	{
		list<DIRECTION_TYPE> makeDoor;	//�濡�� ���� ���� ������ �־�д�.
		do
		{
			for (int i = 0; i < 4; i++)
			{
				if (*nowMake / 9 == 0 && i == 0)	//������ �� �̸� ����
					continue;
				if (*nowMake / 9 == 8 && i == 1)
					continue;
				if (*nowMake % 9 == 0 && i == 2)
					continue;
				if (*nowMake % 9 == 8 && i == 3)
					continue;
				if (!(map[*nowMake / 9][*nowMake % 9]->IsDoor((DIRECTION_TYPE)i)))	//���� ������
				{
					if (random(100) < 80 - (index*3))	//Ȯ���� ���� �������� 80%����
					{
						if (random(2))
							makeDoor.push_back((DIRECTION_TYPE)i);
						else
							makeDoor.push_front((DIRECTION_TYPE)i);
					}
				}
			}
		}while (makeDoor.size() == 0 && *nowMake == 40);	//do while������ ���ֳ�

		for (; makeDoor.size() != 0;)	//�ϳ��� ������ ���� �����
		{
			switch (makeDoor.front())
			{
			case UP:
				if (!(map[(*nowMake / 9) - 1][*nowMake % 9]->IsUse()))	
					nextMake.push_back(*nowMake - 9);					//push_back�� insert�� �ٲٸ� ���̿켱�� �ȴ�
				map[*nowMake / 9][*nowMake % 9]->isDoor[UP] = true;
				map[(*nowMake / 9) - 1][*nowMake % 9]->isDoor[DOWN] = true;
				break;
			case DOWN:
				if (!(map[(*nowMake / 9) + 1][*nowMake % 9]->IsUse()))
					nextMake.push_back(*nowMake + 9);
				map[*nowMake / 9][*nowMake % 9]->isDoor[DOWN] = true;
				map[(*nowMake / 9) + 1][*nowMake % 9]->isDoor[UP] = true;
				break;
			case LEFT:
				if (!(map[*nowMake / 9][(*nowMake % 9) - 1]->IsUse()))
					nextMake.push_back(*nowMake - 1);
				map[*nowMake / 9][*nowMake % 9]->isDoor[LEFT] = true;
				map[*nowMake / 9][(*nowMake % 9) - 1]->isDoor[RIGHT] = true;
				break;
			case RIGHT:
				if (!(map[*nowMake / 9][(*nowMake % 9) + 1]->IsUse()))
					nextMake.push_back(*nowMake + 1);
				map[*nowMake / 9][*nowMake % 9]->isDoor[RIGHT] = true;
				map[*nowMake / 9][(*nowMake % 9) + 1]->isDoor[LEFT] = true;
				break;
			}
			makeDoor.pop_front();
		}
	}
	//nextMake�� �̿��ؼ� �ȿ� ���뵵 ä������ҵ��ϴ�
	MapInfo mapInfo;
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (map[y][x]->IsUse())
				mapInfo.SetRoom(map[y][x]);
		}
	}
}
GameManager* GameManager::GetInstance()
{
	if (singleton == NULL)
		singleton = new GameManager();
	return singleton;
}
void GameManager::KeyEvent()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)//(��)
	{
		this->player->Move(UP);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)//(�Ʒ�)
	{
		this->player->Move(DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//(��)
	{
		this->player->Move(LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//(����)
	{
		this->player->Move(RIGHT);
	}

	if (GetAsyncKeyState(0x57) == (short)0x8001)	//(W)��
		this->player->SetLookingDir(UP);
	if (GetAsyncKeyState(0x53) == (short)0x8001)	//(S)�Ʒ�
		this->player->SetLookingDir(DOWN);
	if (GetAsyncKeyState(0x41) == (short)0x8001)	//(A)��
		this->player->SetLookingDir(LEFT);
	if (GetAsyncKeyState(0x44) == (short)0x8001)	//(D)����
		this->player->SetLookingDir(RIGHT);

	if (GetAsyncKeyState(0x45) == (short)0x8001)	//(E)��ȣ�ۿ�
	{
		if (!(this->player->IsWall(this->player->GetLookingDir())))
		{
			Object * target = this->player->CheckCollision(this->player->GetLookingDir());
			if (target != NULL)
				target->Interact(*(this->player));
		}
	}
	if (GetAsyncKeyState(VK_RETURN) == (short)0x8001)	//(����) ���� �޼���
	{
		NextMessage();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)//(�����̽�)����
	{
		this->player->Attack();
	}

	if (GetAsyncKeyState(0x50) & 0x0001)//(P)�Ͻ�����
		this->SetGameState(PAUSE);
}
void GameManager::DrawFrame()		//�����ӱ׸���
{
	gotoxy(0, 0);
	for (int i = 0; i < 52; i++)
		cout << "��";
	for (int i = 1; i < 32; i++)
	{
		gotoxy(0, i);
		cout << "��";
		gotoxy(102, i);
		cout << "��";
	}
	gotoxy(0, 31);
	for (int i = 0; i < 52; i++)
		cout << "��";
	for (int i = 32; i < 37; i++)
	{
		gotoxy(0, i);
		cout << "��";
		gotoxy(70, i);
		cout << "��";
		gotoxy(102, i);
		cout << "��";
	}
	gotoxy(0, 37);
	for (int i = 0; i < 52; i++)
		cout << "��";
}
void GameManager::DrawStartPage()
{
	static int count = 0;	//ȭ�� ���ī��� (0���� 50����)
	static bool isPrint = true;	//ȭ�� ��� ����(press ..)
	
	int titleX = 49, titleY = 15;	//���� ��ġ
	int explanX = 40, explanY = 22;	//���� ��ġ
	//����ȭ�� ���
	gotoxy(titleX,titleY);		//����
	cout << "Duntam";

	if (count == 50)	//(press ..)���ڰŸ��� �ϱ��
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			cout << "                        ";
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			cout << "Press spacebar to start!";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawPausePage()
{
	static int count = 0;	//ȭ�� ��� ī��Ʈ (0���� 50����)
	static bool isPrint = true;	//ȭ�� ��� ����(���� ��ġ)

	int mapX = 16, mapY = 1;		//���� ���� ��ġ
	//�Ͻ����� ȭ�� ���
	//�����
	//this->PrintMap(mapX, mapY);		//��� �ɵ�(����ȭ�Ҷ� 1������)
	//���� ��ġ ǥ��(������)
	if (count == 30)
	{
		if (isPrint)
		{
			gotoxy(mapX + (this->nowMapX * 8) + 2, mapY + (this->nowMapY * 4) + 1);
			cout << "��";
			isPrint = false;
		}
		else
		{
			gotoxy(mapX + (this->nowMapX * 8) + 2, mapY + (this->nowMapY * 4) + 1);
			cout << "  ";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawGameOverPage()
{
	//���ӿ��� ȭ�� ���
	static int count = 0;	//ȭ�� ���ī��� (0���� 50����)
	static bool isPrint = true;	//ȭ�� ��� ����(press ..)

	int titleX = 47, titleY = 15;	//���� ��ġ
	int explanX = 37, explanY = 22;	//���� ��ġ
									//����ȭ�� ���
	gotoxy(titleX, titleY);		//����
	cout << "Game Over!";

	if (count == 50)	//(press ..)���ڰŸ��� �ϱ��
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			cout << "                              ";
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			cout << "Press spacebar to go startmenu";
			isPrint = true;
		}
		count = 0;
	}
	count++;
}
void GameManager::DrawChangeMap()
{
	for (int y = 0; y < 30; y++)
	{
		gotoxy(2, 1 + y);
		for (int x = 0; x < 50; x++)
			cout << "  ";
	}
}
void GameManager::PrintPlayerState()
{

	gotoxy(2, 35);
	cout << "HP : " << to_string(player->health) << "  ";
}
void GameManager::GameSetting(int mode)
{
	//�ʻ���
	if (mode == 0)
		this->CreateMap();
	else
		this->CreateDebugMap();
	//�÷��̾� ����
	player = new Player(24,14);
	//������Ʈ ����Ʈ �����Ͱ� ����
	this->nowObjectList = &(map[4][4]->objectList);
	this->nowMapX = 4;
	this->nowMapY = 4;
	//�޼��� ����
	this->message.clear();
	//�ݸ��� ���̺� ����
	for (int i = 0; i < 30; i++)	//�ݸ��� ���̺� �� �ʱ�ȭ
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//�ݸ��� ���̺� ����
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	player->SetCollision(NONE);
}
void GameManager::ObjectUpdate()		//������Ʈ����Ʈ ���鼭 Update()����
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	list<Object*>::iterator nextiter = iter;
	for (;iter != this->nowObjectList->end();)
	{
		nextiter++;
		(*iter)->Update();
		iter = nextiter;
	}
	player->Update();
}
void GameManager::ObjectDraw()		//������Ʈ����Ʈ ���鼭 Draw()����
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Draw();
	player->Draw();
}
void GameManager::SetMessage(list<string>& newMessage)
{
	//������ �޼��� ���� �� ���� ����
	this->message.clear();
	this->message.assign(newMessage.begin(), newMessage.end());
	//ù�޼��� ���
	gotoxy(72, 34);
	cout << "                              ";
	gotoxy(72, 34);
	cout << this->message.front();
	this->message.pop_front();

}
void GameManager::NextMessage()
{
	gotoxy(72, 34);
	cout << "                              ";
	gotoxy(72, 34);
	if (this->message.size() != 0)
	{
		//�޼��� ���
		cout << this->message.front();
		//����Ʈ���� ����
		this->message.pop_front();
	}
}
DIRECTION_TYPE GameManager::IsMapChange()
{
	if (player->GetPositionX() == 24 && player->GetPositionY() == 0)
		return UP;
	else if (player->GetPositionX() == 24 && player->GetPositionY() == 29)
		return DOWN;
	else if (player->GetPositionX() == 0 && player->GetPositionY() == 14)
		return LEFT;
	else if (player->GetPositionX() == 49 && player->GetPositionY() == 14)
		return RIGHT;
	else
		return NONE;
}
void GameManager::ChangeMap(DIRECTION_TYPE dir)	//���̵�
{
	
	if (dir == UP)				//���� ����ǥ ����
		this->nowMapY -= 1;
	else if (dir == DOWN)
		this->nowMapY += 1;
	else if (dir == LEFT)
		this->nowMapX -= 1;
	else if (dir == RIGHT)
		this->nowMapX += 1;

	this->player->RemoveAfterimage();	//�ܻ� �̸� ����

	if (dir == UP)				//�÷��̾� ��ġ ����
		this->player->SetPosition(25,29);
	else if (dir == DOWN)
		this->player->SetPosition(25, 0);
	else if (dir == LEFT)
		this->player->SetPosition(49, 15);
	else if (dir == RIGHT)
		this->player->SetPosition(0, 15);

	

	if ((nowMapX < 0 || nowMapX >= 9) || (nowMapY < 0 || nowMapY >= 9))	//�ʹ��� ���� ����� �صа�
		for (;;)
			cout << "map range_out";

	this->nowObjectList = &(map[nowMapY][nowMapX]->objectList);	//������Ʈ����Ʈ�� �����Ͱ� ����


	for (int i = 0; i < 30; i++)		//�ݸ��� ���̺� �� �ʱ�ȭ
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//�ݸ��� ���̺� ����
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	this->player->SetCollision(NONE);

	//���÷���
	DrawChangeMap();
}
void GameManager::SetGameState(GAMESTATE_TYPE state)
{
	system("cls");
	if (state == GAMING)
		this->DrawFrame();
	else if(state == PAUSE)
		this->PrintMap(16, 1);	//���� ������ġ
	this->gameState = state;
}
GameManager* GameManager::singleton;

//�ʻ���
//�� �ൿ���	�̰� ���� �˾Ƽ� �ض���ؾ��Ѵ�
//��ο�
//��ȣ ����(����)	�ƹ����� ��ӹ��� ����� ���Ͽ� ���Խ����ִ°ɷ�