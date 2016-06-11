#include "Thing.h"
#include "GameManager.h"
#include "Bullet.h"

using namespace std;

Thing::Thing(int posX, int posY) : Object(posX, posY)
{
	this->moveDelayMax = 1;
	this->health = 1;
	this->frozing = 0;
}
Thing::~Thing() {}
void Thing::Damage(int p) {}
void Thing::Heal(int p) {}

AltarOfLuck::AltarOfLuck(int posX, int posY) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 2;
	this->drawCount = 0;
	this->instractionCount = 0;
}
AltarOfLuck::~AltarOfLuck() {}
void AltarOfLuck::Attack() {}
void AltarOfLuck::Update() {}
void AltarOfLuck::Draw()
{
	//RemoveAfterimage();
	if (drawCount < 15)
	{
		SetColor(10, 16);
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
		SetColor(7, 16);
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "��";
	}
	else
	{
		SetColor(12, 16);
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
		SetColor(7, 16);
		gotoxy(2 + (positionX * 2), 1 + positionY + 1);
		cout << "��";
	}
	drawCount++;
	if (drawCount >= 30)
		drawCount = 0;
}
void AltarOfLuck::Interact(Object& target)
{
	list<string> message;
	if (instractionCount == 0)
	{
		message.push_back("����� ����");
		message.push_back("���� ���ٸ� ������");
		message.push_back("���� ���ڸ� ������");
		instractionCount++;
	}
	else if (instractionCount == 1)
	{
		if (random(2))
			target.Heal(10);
		else
			target.Damage(5);
		instractionCount++;
	}
	else
	{
		message.push_back("���ϴ� ����̱⸦...");
	}
	GameManager::GetInstance()->SetMessage(message);
}

BulletTrap::BulletTrap(int posX, int posY, DIRECTION_TYPE dir) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->instractionCount = 0;
	this->lookingDir = dir;
	this->attackDelay = 10;
	this->attackDelayMax = 10;
}
BulletTrap::~BulletTrap() {}
void BulletTrap::Attack()
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
void BulletTrap::Update()
{
	if (attackDelay)
		attackDelay--;
	else
	{
		Attack();
		attackDelay = attackDelayMax;
	}
}
void BulletTrap::Draw()
{
	//RemoveAfterimage();
	if (lookingDir == UP)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	else if (lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	else if (lookingDir == LEFT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	else if (lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
}
void BulletTrap::Interact(Object& target)
{
	list<string> message;
	if (instractionCount == 0)
	{
		message.push_back("������ ���� �ɴٴ�");
		message.push_back("��¯�� �ε��ϱ�");
		instractionCount++;
	}
	else if (instractionCount == 1)
	{
		target.Heal(1);
		message.push_back("���� ����� ������ ����");
		instractionCount++;
	}
	else if (instractionCount < 10)
	{
		target.Heal(1);
		message.push_back("���� �峪? �� ����!");
		instractionCount++;
	}
	else
	{
		message.push_back("������ ��");
	}
	GameManager::GetInstance()->SetMessage(message);
}
