#include "Player.h"
#include "GameManager.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->sizeX = 2;
	this->sizeY = 4;
	this->moveDelayMax = 5;
	this->health = 10;
	this->frozing = 0;
}

Player::~Player()
{

}

void Player::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
}
void Player::Draw()		//���� ��ǥ�� ����ϴ°� ���� �� �ϴ�
{
	static int count = 0;
	//������ ���� �׸� �����(���� ������ �ҵ�)
	RemoveAfterimage();
	//�̹��� ���
	if(frozing)
		SetColor(11, 16);
	if (count < 10)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << " �� ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "<��>";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << "  > ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 3);
		cout << " �� ";
	}
	else
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << " �� ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "<��>";
		gotoxy(2 + (positionX * 2), 1 + positionY + 2);
		cout << " <  ";
		gotoxy(2 + (positionX * 2), 1 + positionY + 3);
		cout << " �� ";
	}
	SetColor(7, 16);
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