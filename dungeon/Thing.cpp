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
	this->interactionCount = 0;
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
	if (interactionCount == 0)
	{
		message.push_back("����� ����");
		message.push_back("���� ���ٸ� ������");
		message.push_back("���� ���ڸ� ������");
		interactionCount++;
	}
	else if (interactionCount == 1)
	{
		if (random(2))
			target.Heal(10);
		else
			target.Damage(5);
		interactionCount++;
	}
	else
	{
		message.push_back("���ϴ� ����̱⸦...");
	}
	GameManager::GetInstance()->SetMessage(message);
}
AltarOfHeal::AltarOfHeal(int posX, int posY) : AltarOfLuck(posX, posY){}
void AltarOfHeal::Draw()
{
	SetColor(12, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "��";
	SetColor(7, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY + 1);
	cout << "��";
}
void AltarOfHeal::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("ġ���� ����");
		message.push_back("�״뿡�� ������...");
		interactionCount++;
	}
	else
	{
		target.Heal(10);
		message.push_back("��ȸ�� �ѹ���...");
	}
	GameManager::GetInstance()->SetMessage(message);
}
AltarOfHeal::~AltarOfHeal() {}
BulletTrap::BulletTrap(int posX, int posY, DIRECTION_TYPE dir) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
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
	if (drawCount == 0)
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
		drawCount++;
	}
}
void BulletTrap::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("������ ���� �ɴٴ�");
		message.push_back("��¯�� �ε��ϱ�");
		interactionCount++;
	}
	else if (interactionCount == 1)
	{
		target.Heal(1);
		message.push_back("���� ����� ������ ����");
		interactionCount++;
	}
	else if (interactionCount < 10)
	{
		target.Heal(1);
		message.push_back("���� �峪? �� ����!");
		interactionCount++;
	}
	else
	{
		message.push_back("������ ��");
	}
	GameManager::GetInstance()->SetMessage(message);
}

Teleporter::Teleporter(int posX, int posY, int warpX, int warpY) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->drawCount = 0;
	this->warpPointX = warpX;
	this->warpPointY = warpY;
}
Teleporter::~Teleporter () {}
void Teleporter::Attack() {}
void Teleporter::Update() {}
void Teleporter::Draw()
{
	//RemoveAfterimage();
	if(drawCount < 60)
		SetColor(11, 16);
	else
	{
		if (random(2))
			SetColor(12, 16);
		else
			SetColor(14, 16);
	}

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "��";

	SetColor(7, 16);
	drawCount++;
	if (drawCount >= 120)
		drawCount = 0;
}
void Teleporter::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("�ڷ�����");
		message.push_back("������ ��ġ�� �̵��մϴ�");
		interactionCount++;
	}
	else
	{
		if (CheckCollision(warpPointX, warpPointY) == NULL)
		{
			message.push_back("����!");
			target.SetPosition(warpPointX, warpPointY);
		}
		else
		{
			message.push_back("������ ��ǥ�� ���� �ֽ��ϴ�");
			message.push_back("����� �ٽ� �õ��Ͻʽÿ�");
		}
	}
	GameManager::GetInstance()->SetMessage(message);
}

Teleporter_sounghoo::Teleporter_sounghoo(int posX, int posY, int warpX, int warpY) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->warpPointX = warpX;
	this->warpPointY = warpY;
	this->TypeName = 52;

	//if (CheckCollision(warpPointX, warpPointY) == NULL)
	//{
	//	this->warpPointX = this->positionX;
	//	this->warpPointY = this->positionY;
	//	this->warpPoint = this;
	//}
	//else if (CheckCollision(warpPointX, warpPointY)->TypeName == 52) // ��Ż ��ǥ�� ��Ż���� Ȯ��
	//{
	//	Teleporter_sounghoo* other = (Teleporter_sounghoo*)CheckCollision(warpPointX, warpPointY);
	//	this->warpPoint = other;
	//	other->warpPoint = this;
	//	other->warpPointX = this->positionX;
	//	other->warpPointY = this->positionY;
	//}
}
Teleporter_sounghoo::~Teleporter_sounghoo() {}
void Teleporter_sounghoo::Attack() {}
void Teleporter_sounghoo::Update() {}
void Teleporter_sounghoo::Draw()
{
	SetColor(10, 16);

	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "��";

	SetColor(7, 16);
}
void Teleporter_sounghoo::Interact(Object& target)
{
	DIRECTION_TYPE dir = target.GetLookingDir();

	int x = 0, y = 0;

	switch (dir)
	{
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	}

	target.SetPosition(warpPointX + x, warpPointY + y);
}

ClearObject::ClearObject(int posX, int posY) : Thing(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 2;
	this->drawCount = 0;
	this->interactionCount = 0;
}
ClearObject::~ClearObject() {}
void ClearObject::Attack() {}
void ClearObject::Update() {}
void ClearObject::Draw()
{
	//RemoveAfterimage();

	SetColor(drawCount + 9, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY);
	cout << "��";
	SetColor(15, 16);
	gotoxy(2 + (positionX * 2), 1 + positionY + 1);
	cout << "��";
	drawCount++;
	if (drawCount >= 7)
		drawCount = 0;
	SetColor(7, 16);
}
void ClearObject::Interact(Object& target)
{
	list<string> message;
	if (interactionCount == 0)
	{
		message.push_back("���� �ź��� ��ü");
		message.push_back("������ �������� �ٽ� ���� �ɰ�");
		interactionCount++;
	}
	else
	{
		GameManager::GetInstance()->SetGameState(GAMECLEAR);
	}
	GameManager::GetInstance()->SetMessage(message);
}