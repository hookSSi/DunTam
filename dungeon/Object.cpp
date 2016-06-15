#include "Object.h"
#include "GameManager.h"

Object::Object(int posX, int posY)
{
	this->positionX = posX;
	this->positionY = posY;
	this->lookingDir = NONE;
	this->prevMove = NONE;
	this->moveDelay = 0;
	this->frozing = 0;
	this->TypeName = 0;
	this->interactionCount = 0;
	this->drawCount = 0;
}

Object::~Object()
{

	if(GameManager::GetInstance()->gameState == GAMING)
		GameManager::GetInstance()->nowObjectList->remove(this);

}
void Object::Move(DIRECTION_TYPE dir)
{
	if (moveDelay > 0)	//�������� �Ǵ��� Ȯ��
		return;
	if (health <= 0)	//�Ǵ� �ִ���
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

		lookingDir = dir;

		if (frozing)		//������ ����
			moveDelay = moveDelayMax * 3; //frozing �����϶� 3�� ������
		else
			moveDelay = moveDelayMax;
	}
	else if (CheckCollision(dir)->TypeName == 52)
	{
		CheckCollision(dir)->Interact(*this);
	}
}
// Object::Move(int p_x, int p_y,DIRECTION_TYPE dir)
//{
//	if (moveDelay > 0)	//�������� �Ǵ��� Ȯ��
//		return;
//	//�̵� ���� ������ �浹 Ȯ���ϰ�
//	//�̵�ó�� �ݸ��� ���̺����(�浹���̺����)
//	Object * target = NULL;
//
//	if (IsWall(p_x,p_y))
//		return;
//
//	if (CheckCollision(p_x,p_y) == NULL)	//�浹 Ȯ��
//	{
//		SetPosition(p_x, p_y);
//		SetCollision(NONE);	//�浹 ���̺� ����
//		prevMove = dir;		//������ ����(Draw��)
//
//		lookingDir = dir;
//
//		if (frozing)		//������ ����
//			moveDelay = moveDelayMax * 3; //frozing �����϶� 2�� ������
//		else
//			moveDelay = moveDelayMax;
//	}
//}
Object* Object::CheckCollision(DIRECTION_TYPE dir)
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
Object* Object::CheckCollision(int posX, int posY)
{
	Object* target = NULL;
	target = GameManager::GetInstance()->collisionTable[posY][posX];
	return target;
}
void Object::ClearImage()
{
	for (int y = 0; y < sizeY; y++)
	{
		gotoxy((positionX * 2) + 2, positionY + y + 1);
		for (int x = 0; x < sizeX; x++)
			printf("  ");
	}
}
void Object::ClearCollision()
{
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
			GameManager::GetInstance()->collisionTable[positionY + y][positionX + x] = NULL;
}
void Object::SetCollision(DIRECTION_TYPE dir)
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
bool Object::IsWall(DIRECTION_TYPE dir)	//�ε����� �Ѿ�� true ���������� false
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
bool Object::IsWall(int p_x, int p_y)	//�ε����� �Ѿ�� false ���������� true
{
	if ((0 <= p_x && p_x + sizeX - 1 < 50) && (0 <= p_y && p_y + sizeY - 1 < 30))
		return true;
	else
		return false;
}
void Object::RemoveAfterimage()
{
	if (prevMove != NONE)
	{
		if (prevMove == UP)
		{
			gotoxy((positionX * 2) + 2, positionY + sizeY + 1);
			for (int i = 0; i < sizeX; i++)
				printf("  ");
		}
		else if (prevMove == DOWN)
		{
			gotoxy((positionX * 2) + 2, positionY - 1 + 1);
			for (int i = 0; i < sizeX; i++)
				printf("  ");
		}
		else if (prevMove == LEFT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) + (sizeX * 2) + 2, positionY + 1 + i);
				printf("  ");
			}
		}
		else if (prevMove == RIGHT)
		{
			for (int i = 0; i < sizeY; i++)
			{
				gotoxy((positionX * 2) - 2 + 2, positionY + 1 + i);
				printf("  ");
			}
		}
		prevMove = NONE;
	}
}
int Object::GetPositionX()
{
	return this->positionX;
}
int Object::GetPositionY()
{
	return this->positionY;
}
int Object::GetSizeX()
{
	return sizeX;
}
void Object::SetSizeX(int p_size)
{
	sizeX = p_size;
}
int Object::GetSizeY()
{
	return sizeY;
}
void Object::SetSizeY(int p_size)
{
	sizeY = p_size;
}
void Object::SetDrawCountZero()
{
	this->drawCount = 0;
}
void Object::SetPosition(int posX, int posY)
{
	this->ClearCollision();
	this->ClearImage();
	if (posX + sizeX - 1 < 50 && posX >= 0)
		this->positionX = posX;
	else if (posX < 0)
		this->positionX = 0;
	else
		this->positionX = 49 - sizeX + 1;
	
	if (posY + sizeY - 1 < 30 && posY >= 0)
		this->positionY = posY;
	else if (posY < 0)
		this->positionY = 0;
	else
		this->positionY = 29 - sizeY + 1;
	this->SetCollision(NONE);
}
void Object::Damage(int p)
{
	this->health -= p;
	if (this->health <= 0)
		this->Die();
}
void Object::Heal(int p)
{
	this->health += p;
	if (health > 100000000)
		health = 100000000;
}
void Object::Frozing(int p)
{
	this->frozing += p;
	if (frozing > 100000000)
		frozing = 100000000;
}
void Object::SetLookingDir(DIRECTION_TYPE dir)
{
	if (dir != NONE)
		lookingDir = dir;
}
DIRECTION_TYPE Object::GetLookingDir()
{
	return lookingDir;
}
void Object::Die()
{
	//dieObjectList�� �ְ�
	GameManager::GetInstance()->dieObjectList.push_back(this);
	//�ݸ������̺��� �����
	this->ClearCollision();
	//ȭ�鿡 �׷����͵� �����
	this->ClearImage();
	this->RemoveAfterimage();
}