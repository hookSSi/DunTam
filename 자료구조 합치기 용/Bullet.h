#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~Bullet();
	virtual void Update();		//�������� ó���� ��
	virtual void Draw();		//�׷����� �κ� ó��
	virtual void Interact(Object& target);	//��ȣ�ۿ�
	virtual void Damage(int p);	//������ ����
	virtual void Heal(int p);	//ġ�� ����
};

class EnemyBullet : public Object
{
	EnemyBullet(int posX, int posY, DIRECTION_TYPE lookingDir);
	~EnemyBullet();
	virtual void Update();		//�������� ó���� ��
	virtual void Draw();		//�׷����� �κ� ó��
	virtual void Interact(Object& target);	//��ȣ�ۿ�
	virtual void Damage(int p);	//������ ����
	virtual void Heal(int p);	//ġ�� ����
};