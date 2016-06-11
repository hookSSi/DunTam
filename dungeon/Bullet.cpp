#include "Bullet.h"
#include "GameManager.h"

using namespace std;

Bullet::Bullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Object(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 3;
	this->moveDelay = 3;
	this->health = 1;
	this->frozing = 0;
	this->lookingDir = lookingDir;
	//��ġ �缳��
	if (lookingDir == UP)
		this->positionY -= 1;
	else if (lookingDir == DOWN)
		this->positionY += 1;
	else if (lookingDir == LEFT)
		this->positionX -= 1;
	else if (lookingDir == RIGHT)
		this->positionX += 1;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	if (moveDelay == 0)
	{
		Move(lookingDir);
	}
	if (moveDelay == 0)
	{
		if (!IsWall(lookingDir))
		{
			Object* target = CheckCollision(lookingDir);
			if (target != NULL)
				target->Damage(1);
		}
		this->Die();
	}
}
void Bullet::Draw()
{
	//������ ���� �׸� �����
	RemoveAfterimage();

	SetColor(14, 16);
	if (lookingDir == UP || lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	SetColor(7, 16);
}
void Bullet::Interact(Object& targer)
{
	list<string> message;
	message.push_back("�� ��ٻ�� �Ѿ�����");
	message.push_back("���Ŵ� ������ ���ֳ�");
	message.push_back("�����ض� ���ž�");
	GameManager::GetInstance()->SetMessage(message);
}
void Bullet::Damage(int p){}
void Bullet::Heal(int p){}

//
//	�� �Ѿ�
//
EnemyBullet::EnemyBullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Object(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 3;
	this->moveDelay = 3;
	this->health = 1;
	this->frozing = 0;
	this->lookingDir = lookingDir;
	//��ġ �缳��
	if (lookingDir == UP)
		this->positionY -= 1;
	else if (lookingDir == DOWN)
		this->positionY += 1;
	else if (lookingDir == LEFT)
		this->positionX -= 1;
	else if (lookingDir == RIGHT)
		this->positionX += 1;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	if (moveDelay == 0)
	{
		Move(lookingDir);
	}
	if (moveDelay == 0)
	{
		if (!IsWall(lookingDir))
		{
			Object* target = CheckCollision(lookingDir);
			if (target != NULL)
				target->Damage(1);
		}
		this->Die();
	}
}
void EnemyBullet::Draw()
{
	//������ ���� �׸� �����
	RemoveAfterimage();

	SetColor(14, 16);
	if (lookingDir == UP || lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		cout << "��";
	}
	SetColor(7, 16);
}
void EnemyBullet::Interact(Object& targer)
{
	list<string> message;
	message.push_back("�� ��ٻ�� �Ѿ�����");
	message.push_back("���Ŵ� ������ ���ֳ�");
	message.push_back("�����ض� ���ž�");
	GameManager::GetInstance()->SetMessage(message);
}
void EnemyBullet::Damage(int p) {}
void EnemyBullet::Heal(int p) {}
