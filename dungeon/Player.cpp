#include "Player.h"
#include "GameManager.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 3;
	this->moveDelay = 0;
	this->moveDelayMax = 10;
	this->health = 10;
}

Player::~Player()
{

}

void Player::Update()
{
	if (moveDelay)
		moveDelay--;
}
void Player::Draw()		//���� ��ǥ�� ����ϴ°� ���� �� �ϴ�
{
	static int count = 0;
	//������ ���� �׸� �����(���� ������ �ҵ�)
	if (prevMove != NONE)
	{
		if (prevMove == UP)
		{
			gotoxy((positionX * 2) + 2, positionY + sizeY + 1);
			for (int i = 0; i < sizeX; i++)
				cout << "  ";
		}
		else if (prevMove == DOWN)
		{
			gotoxy((positionX * 2) + 2, positionY - 1 + 1);
			for (int i = 0; i < sizeX; i++)
				cout << "  ";
		}
		else if (prevMove == LEFT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) + (sizeX * 2) + 2, positionY + 1 + i);
				cout << "  ";
			}
		}
		else if (prevMove == RIGHT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) - 2 + 2, positionY + 1 + i);
				cout << "  ";
			}
		}
		prevMove = NONE;
	}
	//�̹��� ���
	if (count < 10)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "< ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << "��";
	}
	else
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << " >";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << "��";
	}
	count++;
	if (count >= 20)
		count = 0;
}
void Player::Damage(int p)
{

}
void Player::Heal(int p)
{

}
void Player::Move(DIRECTION_TYPE dir)
{
	if (moveDelay != 0)	//�������� �Ǵ��� Ȯ��
		return;
	//�̵� ���� ������ �浹 Ȯ���ϰ�
	//�̵�ó�� �ݸ��� ���̺����(�浹���̺����)
	Object * target = NULL;
	
	if (IsWall(dir))
		return;

	if (CheckCollision(dir) == NULL)	//�浹 Ȯ��
	{
		SetCollision(dir);	//�浹 ���̺� ����
		prevMove = dir;		//������ ����(Draw��)

		if (dir == UP)		//��ǥ ����
			positionY -= 1;
		else if (dir == DOWN)
			positionY += 1;
		else if (dir == LEFT)
			positionX -= 1;
		else if (dir == RIGHT)
			positionX += 1;

		moveDelay = moveDelayMax;	//������ ����
	}
}
Object* Player::CheckCollision(DIRECTION_TYPE dir)
{
	Object * target = NULL;
	//�ڽ��� �����ϴ� �� ���� üũ�ؼ� �ϳ��� ������ target�� �ּҰ� ���� ������ NULL����
	if (dir == UP)
	{
		for (int i = 0; i < sizeX; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY - 1][positionX + i];
			if (target != NULL)
				break;
		}
	}
	else if (dir == DOWN)
	{
		for (int i = 0; i < sizeX; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + sizeY][positionX + i];
			if (target != NULL)
				break;
		}
	}
	else if (dir == LEFT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + i][positionX - 1];
			if (target != NULL)
				break;
		}
	}
	else if (dir == RIGHT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX];
			if (target != NULL)
				break;
		}
	}
	return target;
}
void Player::SetCollision(DIRECTION_TYPE dir)
{
	if (dir == UP)
	{
		for (int i = 0; i < sizeX; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY - 1][positionX + i] = this;
			GameManager::GetInstance()->collisionTable[positionY + sizeY - 1][positionX + i] = NULL;
		}
	}
	else if (dir == DOWN)
	{
		for (int i = 0; i < sizeX; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + sizeY][positionX + i] = this;
			GameManager::GetInstance()->collisionTable[positionY][positionX + i] = NULL;
		}
	}
	else if (dir == LEFT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + i][positionX - 1] = this;
			GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX - 1] = NULL;
		}
	}
	else if (dir == RIGHT)
	{
		for (int i = 0; i < sizeY; i++)
		{
			GameManager::GetInstance()->collisionTable[positionY + i][positionX + sizeX] = this;
			GameManager::GetInstance()->collisionTable[positionY + i][positionX] = NULL;
		}
	}
	else if (dir == NONE)
	{
		for (int y = 0; y < sizeY; y++)
			for (int x = 0; x < sizeX; x++)
				GameManager::GetInstance()->collisionTable[positionY + y][positionX + x] = this;
	}
}
bool Player::IsWall(DIRECTION_TYPE dir)	//�ε����� �Ѿ�� true ���������� false
{
	if (dir == UP)
	{
		if (positionY - 1 >= 0)
			return false;
		else
			return true;
	}
	else if (dir == DOWN)
	{
		if (positionY + sizeY - 1 + 1 < 30)
			return false;
		else
			return true;
	}
	else if (dir == LEFT)
	{
		if (positionX - 1 >= 0)
			return false;
		else
			return true;
	}
	else if (dir == RIGHT)
	{
		if (positionX + sizeX - 1 + 1 < 50)
			return false;
		else
			return true;
	}
}