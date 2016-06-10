#include "Block.h"
#include "GameManager.h"

using namespace std;

Block::Block(int posX, int posY) : Object(posX,posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 1;
	this->health = 1;
	this->frozing = 0;
}


Block::~Block(){}
void Block::Attack(){}
void Block::Update(){}
void Block::Draw()
{
	RemoveAfterimage();

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "��";
}
void Block::Interact(Object& target)
{
	static int count = 0;
	list<string> message;
	if (count == 0)
	{
		message.push_back("�̺� �� �ǵ�����");
		message.push_back("���� ������ �ϸ�");
		message.push_back("ȥ���� �˾�");
		GameManager::GetInstance()->SetMessage(message);
		count++;
	}
	else
	{
		target.Damage(2);
		message.push_back("�� �ǵ��� ����� �ѰŰ�����");
		message.push_back("�̰� �� �밡��");
		GameManager::GetInstance()->SetMessage(message);
	}
}
void Block::Damage(int p){}
void Block::Heal(int p){}