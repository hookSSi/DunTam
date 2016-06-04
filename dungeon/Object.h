#pragma once

class Object
{
protected:
	int positionX, positionY;	//��ġ��ǥ
	int sizeX, sizeY;			//objectũ��
	int movedelay, movedelaymax;	//������ �����̿� �ִ�
	int health;					//ü��
	//char image;				//�׷��� �̹���

	void Die();
public:
	Object(int posX,int posY);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetCollision() = 0;
	virtual void Damage(int p) = 0;
	virtual void Heal(int p) = 0;
	virtual ~Object();
};