#pragma once
#include"GameManager.h"
#include<string>

using namespace std;

class MapInfo
{
private:
	Room* targetRoom;
	string path;

	int CountFile();	//������ ���� ����
	void SetPath();		//���� ��� ����
	void FillInList();	//����Ʈ�ȿ� �ʳ��� �о �־���
public:
	~MapInfo() { delete targetRoom; }
	void SetRoom(Room * target);	//�� ���� ����(�����ϰ�)
	void SetRoom(Room * target, char * roomName);	//��� ����
};