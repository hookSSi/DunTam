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
	int drawCount;				//drawCount
	int interactionCount;		//��ȣ�ۿ�Count
	DIRECTION_TYPE prevMove;	//���� �̵� ����(Draw��)
	DIRECTION_TYPE lookingDir;	//���� ����	
	//char image;				//�׷��� �̹���

	void Die();
public:
	int TypeName;
	Object(int posX,int posY);
	virtual void Update() = 0;		//�������� ó���� ��
	virtual void Draw() = 0;		//�׷����� �κ� ó��
	virtual void Interact(Object& target) = 0; //��ȣ�ۿ�
	virtual void Move(DIRECTION_TYPE dir);	//�̵� �κ�
	virtual void Move(int p_x, int p_y, DIRECTION_TYPE dir);
	virtual void ClearImage();				//�̹��� ����
	virtual void ClearCollision();			//���̺� ����
	virtual void SetCollision(DIRECTION_TYPE dir);	//�浹 ���̺� ����
	virtual Object* CheckCollision(DIRECTION_TYPE dir);	//�浹 Ȯ��
	virtual Object* CheckCollision(int posX, int posY);	//�浹 Ȯ�� ��ǥ�� Ȯ��
	virtual bool IsWall(DIRECTION_TYPE dir);	//���ӹ����� �������� üũ
	virtual bool IsWall(int p_x, int p_y);
	virtual void RemoveAfterimage();	//�ܻ� ����
	virtual void Damage(int p);	//������ ����
	virtual void Heal(int p);	//ġ�� ����
	virtual int GetPositionX();	//������Ʈ X��ǥ
	virtual int GetPositionY();	//������Ʈ Y��ǥ
	virtual void SetDrawCountZero();	//drawcount  = 0;
	virtual void SetPosition(int posX, int posY);	//������Ʈ ��ǥ ����
	virtual void SetLookingDir(DIRECTION_TYPE dir);	//���� ���� ����
	virtual DIRECTION_TYPE GetLookingDir();			//���� ���� ��
	virtual ~Object();
};

//�޼ҵ� ���� �� �ؾ߰ڴ� ���� �޼ҵ��� ���� ���ε����� ������ �����غ��� ���̴�.