#pragma once
#include "Object.h"
class Thing : public Object
{
public:
	Thing(int posX, int posY);
	virtual void Attack()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void Interact(Object& target)=0;
	virtual void Damage(int p);
	virtual void Heal(int p);
	virtual ~Thing();
};

class AltarOfLuck : public Thing
{
private:
public:
	AltarOfLuck(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~AltarOfLuck();
};
class AltarOfHeal : public AltarOfLuck
{
private:
public:
	AltarOfHeal(int posX, int posY);
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~AltarOfHeal();
};
class BulletTrap : public Thing
{
private:
	DIRECTION_TYPE lookingDir;
	int attackDelay;
	int attackDelayMax;
public:
	BulletTrap(int posX, int posY, DIRECTION_TYPE dir);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~BulletTrap();
};

class Teleporter : public Thing
{
private:
	int warpPointX, warpPointY;	//�����Ǵ� ��ġ
public:
	Teleporter(int posX, int posY, int warpX, int warpY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~Teleporter();
};

class Teleporter_sounghoo : public Thing
{
public:
	int warpPointX, warpPointY;
	Teleporter_sounghoo* warpPoint;
	Teleporter_sounghoo(int posX, int posY, int warpX, int warpY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~Teleporter_sounghoo();
};

class ClearObject : public Thing
{
private:
public:
	ClearObject(int posX, int posY);
	virtual void Attack();
	virtual void Update();
	virtual void Draw();
	virtual void Interact(Object& target);
	virtual ~ClearObject();
};