#include "Player.h"
#include "GameManager.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelay = 0;
	this->moveDelayMax = 60;
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
void Player::Draw()
{

}
void Player::Damage(int p)
{

}
void Player::Heal(int p)
{

}
void Player::Move(DIRECTION_TYPE dir)
{
	//�̵� ���� ������ �浹 Ȯ���ϰ�
	//�̵�ó�� �ݸ��� ���̺����(�浹���̺����)
	Object * target = NULL;
	if (dir == UP)
	{
		if (positionY - 1 >= 0)
		{
			target = GameManager::GetInstance()->collisionTable[positionY - 1][positionX];
			if (target == NULL)
			{
				SetCollision(positionX, positionY, dir);
				positionY -= 1;
			}
		}
	}
	else if (dir == DOWN)
	{
		if (positionY + 1 < 30)
		{
			target = GameManager::GetInstance()->collisionTable[positionY + 1][positionX];
			if (target == NULL)
			{
				SetCollision(positionX, positionY, dir);
				positionY += 1;
			}
		}
	}
	else if (dir == LEFT)
	{
		if (positionX - 1 >= 0)
		{
			target = GameManager::GetInstance()->collisionTable[positionY][positionX - 1];
			if (target == NULL)
			{
				SetCollision(positionX, positionY, dir);
				positionX -= 1;
			}
		}
	}
	else if (dir == RIGHT)
	{
		if (positionY + 1 < 50)
		{
			target = GameManager::GetInstance()->collisionTable[positionY][positionX + 1];
			if (target == NULL)
			{
				SetCollision(positionX, positionY, dir);
				positionX += 1;
			}
		}
	}
	//���� ���ڰ� �� �� ���� �� �ϴ�.
	/*
	if (CheckCollision(dir) == NULL)
	{
		SetCollision(dir);
		prevMove = dir;
		positionX + -= 1;
		positionY + -= 1;
	} �̷� ������ */


}
Object* Player::CheckCollision(int posX, int posY, DIRECTION_TYPE dir)
{
	return NULL;
}

void Player::SetCollision(int posX, int posY, DIRECTION_TYPE dir)
{
	
}