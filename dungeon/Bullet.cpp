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
	this->TypeName = 1;
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
		puts("��");
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		puts("��");
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

	SetColor(12, 16);
	if (lookingDir == UP || lookingDir == DOWN)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		puts("��");
	}
	else if (lookingDir == LEFT || lookingDir == RIGHT)
	{
		gotoxy(2 + (positionX * 2), 1 + positionY);
		puts("��");
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

BombBullet::BombBullet(int posX, int posY, DIRECTION_TYPE lookingDir) : Bullet(posX, posY, lookingDir)
{
	this->moveDelayMax = 2;
	this->moveDelay = 2;
	this->isExplosion = false;
}
BombBullet::~BombBullet() {}
void BombBullet::Update()
{
	Object* target = NULL;
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	//�ֺ��� ���ִ��� üũ
	for (int i = 0; i < 4; i++)
	{
		if (!IsWall((DIRECTION_TYPE)i))
		{
			target = CheckCollision((DIRECTION_TYPE)i);
			if (target != NULL)
			{
				if (target->TypeName == 10)
				{
   					this->isExplosion = true;
					break;
				}
			}
		}
	}
	if (isExplosion)
	{
		//������ ���� ��Ծ�
		for (int y = 0; y < 3; y++)
		{
			int yy = y + positionY - 1;
			for (int x = 0; x < 3; x++)
			{
				int xx = x + positionX - 1;
				if (IsWall(xx, yy))
				{
					if (CheckCollision(xx, yy) != NULL)
					{
						if (CheckCollision(xx, yy)->TypeName == 10)
						{
							CheckCollision(xx, yy)->Damage(1000);
							gotoxy(xx * 2 + 2, yy + 1);
							SetColor(13, 16);
							puts("��");
							SetColor(7, 16);
						}
					}
				}
			}
		}
		this->Die();
		return;
	}
	if (moveDelay == 0)
	{
		Move(lookingDir);
	}
	if (moveDelay == 0)
	{
		this->Die();
	}
}
void BombBullet::Draw()
{
	//������ ���� �׸� �����
	RemoveAfterimage();

	SetColor(13, 16);
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
void BombBullet::Interact(Object& target)
{
	list<string> message;
	message.push_back("�׷��� ��ģ��");
	GameManager::GetInstance()->SetMessage(message);
}

IceArrow::IceArrow(int posX, int posY, DIRECTION_TYPE lookingDir) : Bullet(posX, posY, lookingDir)
{
	this->moveDelayMax = 3;
	this->moveDelay = 3;
}
IceArrow::~IceArrow() {}
void IceArrow::Update()
{
	Object* target = NULL;
	if (moveDelay)
		moveDelay--;

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
				target->Frozing(100);
		}
		this->Die();
	}
}
void IceArrow::Draw()
{
	//������ ���� �׸� �����
	RemoveAfterimage();

	SetColor(11, 16);
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
	SetColor(7, 16);
}
void IceArrow::Interact(Object& target)
{
	list<string> message;
	message.push_back("�ǲ�");
	message.push_back("�ǲ�~!");
	GameManager::GetInstance()->SetMessage(message);
}
void IceArrow::Frozing(int p){}