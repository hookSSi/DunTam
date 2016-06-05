#pragma once

#include "GameFunc.h"

class Object
{
protected:
	int positionX, positionY;	//��ġ��ǥ
	int sizeX, sizeY;			//objectũ��
	int moveDelay, moveDelayMax;//������ �����̿� �ִ�
	int frozing;				//�����̻�(����)
	int health;					//ü��
	DIRECTION_TYPE prevMove;	//���� �̵� ����(Draw��) 
	//char image;				//�׷��� �̹���

	void Die();
public:
	Object(int posX,int posY);
	virtual void Update() = 0;		//�������� ó���� ��
	virtual void Draw() = 0;		//�׷����� �κ� ó��
	virtual void Move(DIRECTION_TYPE dir) = 0;	//�̵� �κ�
	virtual void SetCollision(DIRECTION_TYPE dir) = 0;	//�浹 ���̺� ����
	virtual Object* CheckCollision(DIRECTION_TYPE dir) = 0;	//�浹 Ȯ��
	virtual bool IsWall(DIRECTION_TYPE dir) = 0;	//���ӹ����� �������� üũ
	virtual void Damage(int p) = 0;	//������ ����
	virtual void Heal(int p) = 0;	//ġ�� ����
	virtual ~Object();
};

//�޼ҵ� ���� �� �ؾ߰ڴ� ���� �޼ҵ��� ���� ���ε����� ������ �����غ��� ���̴�.