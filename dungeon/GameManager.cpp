#include "GameManager.h"
#include "ReadMapInfo.h"
#include "Block.h"
#include "Thing.h"

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
Room::~Room()
{
	//�ؾ��Ѵ�
	while (objectList.size() != 0)
	{
		delete objectList.front();
		objectList.pop_front();
	}
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
GameManager::~GameManager()
{
	/*for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			delete map[y][x];
		}
	}*/
	/*for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 50; x++)
			collisionTable[y][x] = NULL;
	}*/

	//delete nowObjectList;	
	//delete player;			
	//delete singleton;
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
				printf("����");
				gotoxy(drawX, drawY + 1);
				printf("��");
				gotoxy(drawX + 4, drawY + 1);
				printf("��");
				gotoxy(drawX, drawY + 2);
				printf("����");
				//��� �׸���
				if (this->map[y][x]->isDoor[UP])
				{
					gotoxy(drawX + 2, drawY - 1);
					printf("��");
				}
				if (this->map[y][x]->isDoor[DOWN])
				{
					gotoxy(drawX + 2, drawY + 3);
					printf("��");
				}
				if (this->map[y][x]->isDoor[LEFT])
				{
					gotoxy(drawX - 2, drawY + 1);
					printf("��");
				}
				if (this->map[y][x]->isDoor[RIGHT])
				{
					gotoxy(drawX + 6, drawY + 1);
					printf("��");
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

	MapInfo mapInfo;

	//���۹�
	map[4][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[4][4], "MapInfo/Debug/02.csv");
	//�� �������
	map[3][4]->isDoor[DOWN] = true;
	map[3][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[3][4], "MapInfo/Debug/04.csv");
	map[3][4]->objectList.push_back(new Boss(1, 1));
	map[3][4]->objectList.push_back(new EnemyA(4, 5));
	map[3][4]->objectList.push_back(new EnemyB(45, 5));
	map[3][4]->objectList.push_back(new EnemyB(47, 5));
	//a*�� �׳��� ��
	map[2][4]->isDoor[DOWN] = true;
	map[2][4]->isDoor[UP] = true;
	mapInfo.SetRoom(map[2][4], "MapInfo/Debug/07.csv");
	map[2][4]->objectList.push_back(new EnemyD(1, 25));
	map[2][4]->objectList.push_back(new EnemyB(1, 27));
	//�̷�Ǫ�� a*
	map[1][4]->isDoor[DOWN] = true;
	map[1][4]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][4], "MapInfo/Debug/00.csv");
	map[1][4]->objectList.push_back(new EnemyD(7,22));
	map[1][4]->objectList.push_back(new EnemyD(1,12));
	map[1][4]->objectList.push_back(new EnemyD(27,12));
	map[1][4]->objectList.push_back(new EnemyD(48,18));
	//���� �Ϲ�
	map[1][5]->isDoor[LEFT] = true;
	map[1][5]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][5], "MapInfo/Debug/01.csv");
	map[1][5]->objectList.push_back(new Teleporter(3, 15, 45, 15));
	//��Ż
	map[1][6]->isDoor[LEFT] = true;
	map[1][6]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][6], "MapInfo/Debug/10.csv");
	map[1][6]->objectList.push_back(new Teleporter_sounghoo(7, 15, 42, 15));
	map[1][6]->objectList.push_back(new Teleporter_sounghoo(42, 15, 7, 15));
	//��Ż�̿��ϴ� a*
	map[1][7]->isDoor[LEFT] = true;
	map[1][7]->isDoor[RIGHT] = true;
	mapInfo.SetRoom(map[1][7], "MapInfo/Debug/05.csv");
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 4, 46, 13));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 13, 46, 4));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 27, 46, 17));
	map[1][7]->objectList.push_back(new Teleporter_sounghoo(46, 17, 46, 27));
	map[1][7]->objectList.push_back(new EnemyD(3, 3));
	map[1][7]->objectList.push_back(new EnemyD(4, 4));
	map[1][7]->objectList.push_back(new EnemyB(3, 27));
	map[1][7]->objectList.push_back(new EnemyB(4, 26));
	//��ź��
	map[1][8]->isDoor[LEFT] = true;
	map[1][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[1][8], "MapInfo/Debug/08.csv");
	map[1][8]->objectList.push_back(new EnemyD(48, 2));
	//����
	map[2][8]->isDoor[UP] = true;
	map[2][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[2][8], "MapInfo/Debug/03.csv");
	map[2][8]->objectList.push_back(new AltarOfHeal(20, 2));
	map[2][8]->objectList.push_back(new AltarOfHeal(30, 2));
	map[2][8]->objectList.push_back(new AltarOfHeal(20, 25));
	map[2][8]->objectList.push_back(new AltarOfHeal(30, 25));
	//��C��
	map[3][8]->isDoor[UP] = true;
	map[3][8]->isDoor[DOWN] = true;
	mapInfo.SetRoom(map[3][8], "MapInfo/Debug/09.csv");
	map[3][8]->objectList.push_back(new EnemyE(48, 28));
	//����
	map[4][8]->isDoor[UP] = true;
	mapInfo.SetRoom(map[4][8], "MapInfo/Debug/06.csv");
	map[4][8]->objectList.push_back(new ClearObject(24, 14));

	map[4][4]->objectList.push_back(new ClearObject(24, 15));

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
	while (true)
	{
		int goal = random(81);
		if (map[goal / 9][goal % 9]->IsUse() && goal != 40)
		{
			map[goal / 9][goal % 9]->objectList.push_back(new ClearObject(24, 14));
			gotoxy(0, 0);
			cout << (goal % 9) << (goal / 9);
			Sleep(100);
			break;
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
	if (GetAsyncKeyState(0x4B) == (short)0x8001)	//(K)�ڻ�
	{
		player->Damage(999);
	}
	if (GetAsyncKeyState(0x51) == (short)0x8001)	//(Q)�����Ŀ�
	{
		player->SetSuperPower(100);
	}
	if (GetAsyncKeyState(0x49) == (short)0x8001)	//(I)����ȭ�� ���
	{
		player->ToggleIceArrow();
	}
	if (GetAsyncKeyState(VK_RETURN) == (short)0x8001)	//(����) ���� �޼���
	{
		NextMessage();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)//(�����̽�)����
	{
		this->player->Attack();
	}
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		this->player->moveDelay = 0;
	}

	if (GetAsyncKeyState(0x50) & 0x0001)//(P)�Ͻ�����
		this->SetGameState(PAUSE);
}
void GameManager::DrawFrame()		//�����ӱ׸���
{
	gotoxy(0, 0);
	for (int i = 0; i < 52; i++)
		printf("��");
	for (int i = 1; i < 32; i++)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(102, i);
		printf("��");
	}
	gotoxy(0, 31);
	for (int i = 0; i < 52; i++)
		printf("��");
	for (int i = 32; i < 37; i++)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(70, i);
		printf("��");
		gotoxy(102, i);
		printf("��");
	}
	gotoxy(0, 37);
	for (int i = 0; i < 52; i++)
		printf("��");
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
void GameManager::DrawGameClearPage()
{
	//���ӿ��� ȭ�� ���
	static int count = 0;	//ȭ�� ���ī��� (0���� 50����)
	static bool isPrint = true;	//ȭ�� ��� ����(press ..)

	int titleX = 47, titleY = 15;	//���� ��ġ
	int explanX = 37, explanY = 22;	//���� ��ġ
									//����ȭ�� ���
	gotoxy(titleX, titleY);		//����
	puts("Game Clear!");
	gotoxy(titleX - 2, titleY + 1);
	puts("Congratulation!!");

	if (count == 50)	//(press ..)���ڰŸ��� �ϱ��
	{
		if (isPrint)
		{
			gotoxy(explanX, explanY);
			puts("                              ");
			isPrint = false;
		}
		else
		{
			gotoxy(explanX, explanY);
			puts("Press spacebar to go startmenu");
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
			printf("  ");
	}
}
void GameManager::PrintPlayerState()
{
	gotoxy(4, 33);
	if (player->superPower > 50000)
	{
		SetColor((player->superPower % 7) + 9, 16);
		printf("SuperPower : ū�� ");
		SetColor(7, 16);
	}
	else if (player->superPower > 1)
	{
		SetColor((player->superPower % 7) + 9, 16);
		printf("SuperPower : %5d", player->superPower);
		SetColor(7, 16);
	}
	else if (player->superPower == 1)
	{
		puts("                    ");
	}
	gotoxy(24, 33);
	if (player->frozing > 50000)
	{
		SetColor(11, 16);
		printf("Frozing : ū�� ");
		SetColor(7, 16);
	}
	else if (player->frozing > 1)
	{
		SetColor(11, 16);
		printf("Frozing : %5d", player->frozing);
		SetColor(7, 16);
	}
	else if (player->frozing == 1)
	{
		puts("                ");
	}
	gotoxy(4, 35);
	cout << "HP : " << to_string(player->health) << "  ";
	if (player->iceArrow)
	{
		SetColor(11, 16);
		puts("IceArrow");
		SetColor(7, 16);
	}
	else
		puts("        ");
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
void GameManager::ClearRoom()
{
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			delete map[y][x];
}
void GameManager::ObjectUpdate()		//������Ʈ����Ʈ ���鼭 Update()����
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (;iter != this->nowObjectList->end(); iter++)
		(*iter)->Update();
	player->Update();
	//������ ó��
	while (dieObjectList.size() != 0)
	{
		delete dieObjectList.front();
		dieObjectList.pop_front();
	}
}
void GameManager::ObjectDraw()		//������Ʈ����Ʈ ���鼭 Draw()����
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->Draw();
	player->Draw();
}
void GameManager::ObjectDrawCountZero()
{
	list<Object*>::iterator iter = this->nowObjectList->begin();
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetDrawCountZero();
	player->SetDrawCountZero();
}
void GameManager::SetMessage(list<string>& newMessage)
{
	//������ �޼��� ���� �� ���� ����
	this->message.clear();

	if (newMessage.size() == 0)
		return;
	this->message.assign(newMessage.begin(), newMessage.end());
	//ù�޼��� ���
	gotoxy(72, 34);
	puts("                              ");
	gotoxy(72, 34);
	cout << this->message.front();
	this->message.pop_front();

}
void GameManager::NextMessage()
{
	gotoxy(72, 34);
	puts("                              ");
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
			puts("map range_out");

	this->nowObjectList = &(map[nowMapY][nowMapX]->objectList);	//������Ʈ����Ʈ�� �����Ͱ� ����


	for (int i = 0; i < 30; i++)		//�ݸ��� ���̺� �� �ʱ�ȭ
		for (int j = 0; j < 50; j++)
			this->collisionTable[i][j] = NULL;

	list<Object*>::iterator iter = this->nowObjectList->begin();	//�ݸ��� ���̺� ����
	for (; iter != this->nowObjectList->end(); iter++)
		(*iter)->SetCollision(NONE);
	this->player->SetCollision(NONE);

	ObjectDrawCountZero();

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