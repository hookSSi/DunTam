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
}
Object* Player::CheckCollision()
{
	return NULL;
}

void Player::SetCollision()
{

}