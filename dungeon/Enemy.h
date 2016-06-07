#pragma once

#include "Object.h"

using namespace std;

class Enemy : public Object
{
protected:
	list<DIRECTION_TYPE>* movingQueue;	//������ ����
	virtual list<DIRECTION_TYPE>* BehaviorPattern() = 0;	//������ť ä���
public:
	Enemy(int posX, int posY);
	virtual void Attack() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~Enemy();
};

class EnemyA : public Enemy
{
protected:
	virtual list<DIRECTION_TYPE>* BehaviorPattern();
public:
	EnemyA(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual ~EnemyA();
};

class EnemyB : public Enemy
{
protected:
	virtual list<DIRECTION_TYPE>* BehaviorPattern();
public:
	EnemyB(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual ~EnemyB();
};