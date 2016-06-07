#include "Player.h"
#include "GameManager.h"
#include "Bullet.h"

Player::Player(int posX,int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 5;
	this->health = 10;
	this->frozing = 0;
	this->lookingDir = DOWN;
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
	//������ ���� �׸� �����
	RemoveAfterimage();
	//�̹��� ���
	if(frozing)
		SetColor(11, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY);
	if (lookingDir == UP)
		cout << "��";
	else if (lookingDir == DOWN)
		cout << "��";
	else if (lookingDir == LEFT)
		cout << "��";
	else if (lookingDir == RIGHT)
		cout << "��";
	else
		cout << "��";
	SetColor(7, 16);
}
void Player::Attack()
{
	if (IsWall(lookingDir))
		return;
	
	Object * target;
	
	target = CheckCollision(lookingDir);
	if (target == NULL)
	{
		GameManager::GetInstance()->nowObjectList->push_back(new Bullet(positionX, positionY, lookingDir));
	}
	else
	{
		target->Damage(1);
	}
}