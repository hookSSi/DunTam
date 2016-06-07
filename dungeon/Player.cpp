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
	this->isDie = false;
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
void Player::Draw()		//시작 좌표를 기록하는게 좋을 듯 하다
{
	//이전에 남은 그림 지우기
	RemoveAfterimage();
	//이미지 출력
	if(frozing)
		SetColor(11, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY);
	if (lookingDir == UP)
		cout << "▲";
	else if (lookingDir == DOWN)
		cout << "▼";
	else if (lookingDir == LEFT)
		cout << "◀";
	else if (lookingDir == RIGHT)
		cout << "▶";
	else
		cout << "★";
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
		GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
	}
	else
	{
		target->Damage(1);
	}
}
void Player::Damage(int p)
{
	this->health -= p;
	if (this->health <= 0)
		this->isDie = true;
}