#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"
//��Ŭ��带 �� ������ҵ�
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
void GameManager::CreateMap()		//���� �̿ϼ�
{
	//���� ��°�� ����...
	for (int y = 0; y < 9; y++) 
		for (int x = 0; x < 9; x++)
			map[y][x] = new Room();

	map[4][4]->isDoor[UP] = true;
	for (int i = 0; i < 20; i++)
		map[4][4]->objectList.push_front(new EnemyB(i, 28));
	
	map[4][4]->objectList.push_back(new EnemyB(2, 2));
	map[4][4]->objectList.push_back(new EnemyB(44, 2));
	map[4][4]->objectList.push_back(new EnemyB(4, 2));
	map[4][4]->objectList.push_back(new EnemyB(40, 2));
	map[4][4]->objectList.push_back(new EnemyB(6, 23));
	map[4][4]->objectList.push_back(new EnemyB(40, 23));
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

	if (GetAsyncKeyState(0x57) == (short)0x8001)
		this->player->SetLookingDir(UP);
	if (GetAsyncKeyState(0x53) == (short)0x8001)
		this->player->SetLookingDir(DOWN);
	if (GetAsyncKeyState(0x41) == (short)0x8001)
		this->player->SetLookingDir(LEFT);
	if (GetAsyncKeyState(0x44) == (short)0x8001)
		this->player->SetLookingDir(RIGHT);

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
	this->PrintMap(mapX, mapY);
	//���� ��ġ ǥ��(������)
	if (count == 50)
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
void GameManager::GameSetting()
{
	//�ʻ���
	this->CreateMap();
	//�÷��̾� ����
	player = new Player(24,14);
	//������Ʈ ����Ʈ �����Ͱ� ����
	this->nowObjectList = &(map[4][4]->objectList);
	this->nowMapX = 4;
	this->nowMapY = 4;
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
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Update();
	player->Update();
}
void GameManager::ObjectDraw()		//������Ʈ����Ʈ ���鼭 Draw()����
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Draw();
	player->Draw();
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
	
	if (dir == UP)				//�÷��̾� ��ġ ����
		this->player->SetPosition(24,29);
	else if (dir == DOWN)
		this->player->SetPosition(24, 0);
	else if (dir == LEFT)
		this->player->SetPosition(0, 14);
	else if (dir == RIGHT)
		this->player->SetPosition(49, 14);


	if ((nowMapX <= 0 || nowMapX >= 9) || (nowMapY <= 0 || nowMapY >= 9))	//�ʹ��� ���� ����� �صа�
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