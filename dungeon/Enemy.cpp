#include "Enemy.h"
#include "GameManager.h"
#include "Bullet.h"
#include "AI_Library.h"

Enemy::Enemy(int posX,int posY) : Object(posX,posY)
{
	this->movingQueue = new list<DIRECTION_TYPE>();
	this->TypeName = 10;
}
Enemy::~Enemy()
{
   	delete movingQueue;
}
list<DIRECTION_TYPE>* Enemy::BehaviorPattern()
{
	return nullptr;
}
EnemyA::EnemyA(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 20;
	this->health = 10;
	this->frozing = 200;
}
EnemyA::~EnemyA()
{
	 
}
void EnemyA::Attack()
{

}
void EnemyA::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
	
	DIRECTION_TYPE nowMove = NONE;

	if (moveDelay == 0)
	{
		if (movingQueue->size() == 0)	//������ť�� ��� �ٽ� ä���ش�
		{
			delete movingQueue;
			movingQueue = BehaviorPattern();
		}
		if (movingQueue->size() != 0)
		{
			nowMove = movingQueue->front();
			Move(nowMove);
			movingQueue->pop_front();
		}
	}
}
void EnemyA::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + (positionX * 2), 1 + positionY);
	puts("��");

	SetColor(7, 16);
}
list<DIRECTION_TYPE>* EnemyA::BehaviorPattern()
{
	list<DIRECTION_TYPE>* movingQueue = new list<DIRECTION_TYPE>();
	movingQueue->push_front((DIRECTION_TYPE)random(4));
	return movingQueue;
}
void EnemyA::Interact(Object& target)
{
	list<string> message;
	message.push_back("�ȳ�");
	message.push_back("�� EnemyA��� ��");
	message.push_back("�� ������ ����");
	message.push_back("�����̾�");
	GameManager::GetInstance()->SetMessage(message);
}

EnemyB::EnemyB(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 2;
	this->sizeY = 2;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
}
void EnemyB::Attack()
{

}
void EnemyB::Update()
{
	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;

	DIRECTION_TYPE nowMove = NONE;
	 
	if (moveDelay == 0)
	{
		if (movingQueue->size() == 0)	//������ť�� ��� �ٽ� ä���ش�
		{
			delete movingQueue;
			movingQueue = BehaviorPattern();
		}
		if (movingQueue->size() != 0)
		{
			nowMove = movingQueue->front();
			Move(nowMove);
			movingQueue->pop_front();
		}
	}
	if (moveDelay == 0)
	{
		if (!IsWall(nowMove))
		{
			Object* target = CheckCollision(nowMove);
			if (target == (Object*)GameManager::GetInstance()->player)
				target->Damage(1);
		}
	}
}
void EnemyB::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + (positionX *  2), 1 + positionY );
	puts("�ſ�");
	gotoxy(2 + (positionX * 2), 1 + positionY + 1);
	puts("ū��");

	SetColor(7, 16);
}
list<DIRECTION_TYPE>* EnemyB::BehaviorPattern()
{
	list<DIRECTION_TYPE>* movingQueue = new list<DIRECTION_TYPE>();
	int pX = GameManager::GetInstance()->player->GetPositionX();
	int pY = GameManager::GetInstance()->player->GetPositionY();

	bool flag[4] = { false,false,false,false };
	if ((this->positionX - pX) > 0)
		flag[2] = true;
	else if ((this->positionX - pX) < 0)
		flag[3] = true;
	if ((this->positionY - pY) > 0)
		flag[0] = true;
	else if ((this->positionY - pY) < 0)
		flag[1] = true;

	if (random(2))
	{
		if(flag[0] == true)
			movingQueue->push_front(UP);
		else if(flag[1] == true)
			movingQueue->push_front(DOWN);
	}
	else
	{
		if (flag[2] == true)
			movingQueue->push_front(LEFT);
		else if(flag[3] == true)
			movingQueue->push_front(RIGHT);
	}

	if(movingQueue->size() == 0)
		movingQueue->push_front((DIRECTION_TYPE)random(4));

	return movingQueue;
}
void EnemyB::Interact(Object& target)
{
	list<string> message;
	message.push_back("ũ�;ƾƾƾƾ� �̸���!");
	message.push_back("���� ���� ũ�ƾ�");
	message.push_back("��ĥ ������ ����");
	message.push_back("�����̾� ũũũũ");
	GameManager::GetInstance()->SetMessage(message);

}
EnemyB::~EnemyB()
{

}

//
//	Enemy C�� ����
//
EnemyC::EnemyC() : Enemy(3, 3)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 5;
	this->m_attackRange = 5;
	this->m_isAttacked = false;
	m_maxAttackDelay = 10;
}

EnemyC::EnemyC(int posX, int posY) : Enemy(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 20;
	this->m_attackRange = 5;
	this->m_isAttacked = false;
	m_maxAttackDelay = 10;
}
void EnemyC::Attack()
{

}
void EnemyC::Attack(DIRECTION_TYPE dir)
{
	if (m_attackDelay > 0)
		return;
	if (IsWall(dir))
		return;

	Object * target;

	target = CheckCollision(dir);
	if (target == NULL)
	{
		GameManager::GetInstance()->nowObjectList->push_back(new EnemyBullet(positionX, positionY, dir));
		GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
	}
	else
	{
		target->Damage(1);
	}

	if (frozing)		//������ ����
		m_attackDelay = m_maxAttackDelay * 3; //frozing �����϶� 2�� ������
	else
		m_attackDelay = m_maxAttackDelay;
}
void EnemyC::Damage(int p_damage)
{
	this->health -= p_damage;
	m_isAttacked = true;
	if (this->health <= 0)
		this->Die();
}
void EnemyC::AI()
{
	Sequence *root = new Sequence;
	AI::CheckStatus *checkStatus = new AI::CheckStatus(moveDelay);
	AI::Detect *detect = new AI::Detect(this);
	AI::SearchingWay *searchingWay = new AI::SearchingWay(this, m_range);
	Sequence *sequence1 = new Sequence;
	Selector *selector1 = new Selector;
	AI::Move *move = new AI::Move(this);
	AI::Attack *attack = new AI::Attack(this, m_attackRange);

	root->AddChild(sequence1);
	sequence1->AddChild(checkStatus); sequence1->AddChild(detect);
	sequence1->AddChild(searchingWay); sequence1->AddChild(selector1);
	selector1->AddChild(attack); selector1->AddChild(move);

	root->Run();
}
void EnemyC::Update()
{

	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
	if (m_attackDelay)
		m_attackDelay--;
	AI();
}
void EnemyC::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + positionX * 2, positionY + 1); // 2+X �� Y + 1 �� �ǹ̰� �����ΰ�??
	puts("��");

	SetColor(7, 16);
}
void EnemyC::Interact(Object& target)
{
	list<string> message;
	message.push_back("...");
	message.push_back("......");
	message.push_back("..............");
	message.push_back(".");
	GameManager::GetInstance()->SetMessage(message);
}
EnemyC::~EnemyC()
{

}
//
//	Enemy D�� ����
//
EnemyD::EnemyD() : EnemyC(3, 3)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 5;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 100;
	this->m_attackRange = 1;
	m_maxAttackDelay = 10;
}

EnemyD::EnemyD(int posX, int posY) : EnemyC(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 5;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 100;
	this->m_attackRange = 1;
	m_maxAttackDelay = 10;
}
void EnemyD::AI()
{
	Sequence *root = new Sequence;
	AI::CheckStatus *checkStatus = new AI::CheckStatus(moveDelay);
	AI::SearchingWay_teleporter *searchingWay = new AI::SearchingWay_teleporter(positionX, positionY, m_range);
	Sequence *sequence1 = new Sequence;
	Selector *selector1 = new Selector;
	AI::Move *move = new AI::Move(this);
	AI::Attack *attack = new AI::Attack(this, m_attackRange);

	root->AddChild(sequence1);
	sequence1->AddChild(checkStatus); sequence1->AddChild(searchingWay); sequence1->AddChild(selector1);
	selector1->AddChild(attack); selector1->AddChild(move);

	root->Run();
}
void EnemyD::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + positionX * 2, positionY + 1); // 2+X �� Y + 1 �� �ǹ̰� �����ΰ�??
	puts("��");

	SetColor(7, 16);
}
void EnemyD::Interact(Object& target)
{
	list<string> message;
	message.push_back("��");
	message.push_back("����");
	message.push_back("���!");
	message.push_back("����");
	GameManager::GetInstance()->SetMessage(message);
}
EnemyD::~EnemyD()
{

}
//
//	EnemyE �� ����
//
EnemyE::EnemyE() : EnemyC(3, 3)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 20;
	this->m_attackRange = 10;
	m_maxAttackDelay = 10;
}

EnemyE::EnemyE(int posX, int posY) : EnemyC(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 1;
	this->moveDelayMax = 10;
	this->health = 10;
	this->frozing = 300;
	this->m_range = 20;
	this->m_attackRange = 10;
	m_maxAttackDelay = 10;
}
void EnemyE::AI()
{
	Sequence *root = new Sequence;
	AI::CheckStatus *checkStatus = new AI::CheckStatus(moveDelay);
	AI::Detect *detect = new AI::Detect(this);
	AI::SearchingWay *searchingWay = new AI::SearchingWay(this, m_range);
	Sequence *sequence1 = new Sequence;
	Selector *selector1 = new Selector;
	AI::Move *move = new AI::Move(this);
	AI::Attack_Dynamic *attackDynamic = new AI::Attack_Dynamic(this, m_attackRange);

	root->AddChild(sequence1);
	sequence1->AddChild(checkStatus); sequence1->AddChild(detect);
	sequence1->AddChild(searchingWay); sequence1->AddChild(selector1);
	selector1->AddChild(attackDynamic); selector1->AddChild(move);

	root->Run();
}
void EnemyE::Draw()
{
	RemoveAfterimage();

	if (frozing)
		SetColor(11, 16);

	gotoxy(2 + positionX * 2, positionY + 1); // 2+X �� Y + 1 �� �ǹ̰� �����ΰ�??
	puts("��");

	SetColor(7, 16);
}
void EnemyE::Interact(Object& target)
{
	list<string> message;
	message.push_back("22");
	message.push_back("1+1");
	message.push_back("2%2");
	message.push_back(".");
	GameManager::GetInstance()->SetMessage(message);
}
EnemyE::~EnemyE()
{

}
//
//	Boss�� ����
//
Boss::Boss() : EnemyC(3, 3)
{
	this->sizeX = 37;
	this->sizeY = 12;
	this->moveDelayMax = 10;
	this->health = 500;
	this->frozing = 0;
	this->m_range = 5;
	this->m_attackRange = 5;
	this->m_isAttacked = false;
	this->m_maxAttackDelay = 10;
}

Boss::Boss(int posX, int posY) : EnemyC(posX, posY)
{
	this->sizeX = 1;
	this->sizeY = 2;
	this->moveDelayMax = 10;
	this->health = 500;
	this->frozing = 0;
	this->m_range = 5;
	this->m_attackRange = 5;
	this->m_isAttacked = false;
	this->m_maxAttackDelay = 10;
}
void Boss::Attack()
{

}
void Boss::Attack(DIRECTION_TYPE dir)
{
	if (m_attackDelay > 0)
		return;
	if (IsWall(dir))
		return;

	Object * target;

	target = CheckCollision(dir);
	if (target == NULL)
	{
		GameManager::GetInstance()->nowObjectList->push_back(new EnemyBullet(positionX, positionY, dir));
		GameManager::GetInstance()->nowObjectList->back()->SetCollision(NONE);
	}
	else
	{
		target->Damage(1);
	}

	if (frozing)		//������ ����
		m_attackDelay = m_maxAttackDelay * 3; //frozing �����϶� 2�� ������
	else
		m_attackDelay = m_maxAttackDelay;
}
void Boss::Damage(int p_damage)
{
	this->health -= p_damage;
	m_isAttacked = true;
	if (this->health <= 0)
		this->Die();
}
void Boss::AI()
{
	Sequence *root = new Sequence;
	AI::CheckStatus *checkStatus = new AI::CheckStatus(moveDelay);
	AI::Detect *detect = new AI::Detect(this);
	AI::SearchingWay *searchingWay = new AI::SearchingWay(this, m_range);
	Sequence *sequence1 = new Sequence;
	Selector *selector1 = new Selector;
	AI::Move *move = new AI::Move(this);
	AI::Attack *attack = new AI::Attack(this, m_attackRange);

	root->AddChild(sequence1);
	sequence1->AddChild(checkStatus); sequence1->AddChild(detect);
	sequence1->AddChild(searchingWay); sequence1->AddChild(selector1);
	selector1->AddChild(attack); selector1->AddChild(move);

	root->Run();
}
void Boss::Update()
{

	if (moveDelay)
		moveDelay--;
	if (frozing)
		frozing--;
	if (m_attackDelay)
		m_attackDelay--;
	AI();
}
void Boss::Draw()
{
	RemoveAfterimage();

	gotoxy(2 + positionX * 2, positionY + 1); // 2+X �� Y + 1 �� �ǹ̰� �����ΰ�??
	puts("\"");
	//gotoxy(2 + positionX * 2 + 11, positionY + 2);
	//puts("J88;");
	//gotoxy(2 + positionX * 2 + 3, positionY + 3);
	//puts("��     JIiii;      ��");
	//gotoxy(2 + positionX * 2 + 3, positionY + 4);
	//puts("���    Ji;;;ii;    ���");
	//gotoxy(2 + positionX * 2 + 4, positionY + 5);
	//puts("��   JIiiiii$$;   ��");
	//gotoxy(2 + positionX * 2 + 4, positionY + 6);
	//puts("����J$$$$$$$$$$;����");
	//gotoxy(2 + positionX * 2 + 6, positionY + 7);
	//puts("J$F'_...._':$;");
	//gotoxy(2 + positionX * 2 + 5, positionY + 8);
	//puts("J8'.��JL  :;��$;");
	//gotoxy(2 + positionX * 2 + 4, positionY + 9);
	//puts("JI8b.��.....'d$$$;");
	//gotoxy(2 + positionX * 2 + 3, positionY + 10);
	//puts("Jiii8$$88888$$iii $;");
	//gotoxy(2 + positionX * 2 + 2, positionY + 11);
	//puts("Jiiiiiiiiiiiiiiiiiii$;");
	//gotoxy(2 + positionX * 2 + 1, positionY + 12);
	//puts("\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"");


	SetColor(7, 16);
}
void Boss::DrawEye(DIRECTION_TYPE dir, int color)
{

}
void Boss::DrawArms(float p_delay)
{

}

void Boss::Interact(Object& target)
{
	list<string> message;
	message.push_back("��դ��ƾ�");
	message.push_back("��");
	message.push_back("�׾�� �ʸ��ڿ�");
	message.push_back("������ 4�� ���� �ɴٴ� �����ӱ���!!!");
	GameManager::GetInstance()->SetMessage(message);
}
Boss::~Boss()
{

}