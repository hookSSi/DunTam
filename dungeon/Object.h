#pragma once

class Object
{
protected:
	int positionX, positionY;	//��ġ��ǥ
	int sizeX, sizeY;			//objectũ��
	int moveDelay, moveDelayMax;//������ �����̿� �ִ�
	int frozing;				//�����̻�(����)
	int health;					//ü��
	//char image;				//�׷��� �̹���

	void Die();
public:
	Object(int posX,int posY);
	virtual void Update() = 0;		//�������� ó���� ��
	virtual void Draw() = 0;		//�׷����� �κ� ó��
	virtual void Move() = 0;		//�̵� �κ�
	virtual void SetCollision() = 0;//�浹 Ȯ��
	virtual void Damage(int p) = 0;	//������ ����
	virtual void Heal(int p) = 0;	//ġ�� ����
	virtual ~Object();
};