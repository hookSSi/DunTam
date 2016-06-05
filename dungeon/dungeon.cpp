/***************************************************
		  ���� ���, �ʻ���, ��ü ����
***************************************************///�����̴� �����̾ƴ϶�
#pragma warning(disable : 4996)

#include"GameManager.h"

using namespace std;

int main()
{
	//==================================================================================���� �� �۾�
	setcursortype(NOCURSOR);				//Ŀ�� �Ⱥ��̱�
	system("mode con: lines=39 cols=104");	//�ܼ�â ����
	
	GameManager *gameManager = GameManager::GetInstance();	//���ӸŴ��� ����

	//===================================================================================�����ӿ�ũ

	int count = 0;
	int timer = time(NULL);
	while (1)
	{
		//�������� �����ϱ� ���� ���۽ð��� �����ð��� ���� ���� ������ ��� �����̸� �ش�
		int start = GetTickCount();


		if (gameManager->gameState == STARTMENU/*���� ����ȭ��*/)
		{
			//����ȭ�� ��� �Լ�
			gameManager->DrawStartPage();
			//�����̽��� ������ ���� ����
			if (GetAsyncKeyState(VK_SPACE) & 0x0001)	//���� ����(�ʻ���) ���ӻ���(������)
			{
				gameManager->GameSetting();
				gameManager->SetGameState(GAMING);
			}
		}

		if(gameManager->gameState == GAMING/*���� ������*/)
		{

			gameManager->ObjectUpdate();	//������Ʈ ������Ʈ

			gameManager->ObjectDraw();	//������Ʈ �׸���

			//Ű���� �̺�Ʈ
			if (GetAsyncKeyState(VK_UP) & 0x8000)//(��)
			{
				gameManager->player->Move(UP);
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)//(�Ʒ�)
			{
				gameManager->player->Move(DOWN);
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)//(��)
			{
				gameManager->player->Move(LEFT);
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//(����)
			{
				gameManager->player->Move(RIGHT);
			}
			if (GetAsyncKeyState(0x50) & 0x0001)//P(�Ͻ�����)
				gameManager->SetGameState(PAUSE);
			//���� ���� �׸���

			if (false/*�� ��ȯ*/)
			{
				DIRECTION_TYPE dir;			//���Ⱚ

				gameManager->ChangeMap(dir);//�ʺ�ȯ
				Sleep(300);					//��� ����� (0.5��)
			}
		}

		if (gameManager->gameState == PAUSE/*�Ͻ� ����*/)
		{
			//�Ͻ� ���� ȭ�� ���
			gameManager->DrawPausePage();
			//Ű �̺�Ʈ Ȯ�� �ϰ� ������ �ٽ� �������� �ƴϸ� ��� ����
			if (GetAsyncKeyState(0x50) & 0x0001)
				gameManager->SetGameState(GAMING);

		}


		if (gameManager->gameState == GAMEOVER/*���� ����*/)
		{
			//���ӿ��� ȭ�� ���
			gameManager->DrawGameOverPage();

			//�׸��� �ٽ� ���� ����ȭ�� true
			if (GetAsyncKeyState(VK_SPACE) & 0x0001)
				gameManager->SetGameState(STARTMENU);
		}


		int wait = (1000/FRAME) - (GetTickCount() - start);
		if(wait >= 0)
			Sleep(wait);
		count++;
		if (timer != time(NULL))
		{
			gotoxy(0, 0);
			cout << "FPS : " << count;
			count = 0;
			timer = time(NULL);
		}
	}
	//================================================================================������ ����
	return 0;
}

//player�� update()
	//�� �����̻��� ī���͸� ���� �ش�
//enemy�� update()
	//�� �����̻��� ī���͸� ���� �ش�
	//�̵��� �����ϸ� �̵����ش�
	//AI�� �˰����� ���� �̵� ����Ʈ�� �־��ش�
//bullet�� update()
	//�̵��� �����ϸ� �̵����ش�
//block�� update()
	//������ �ִ´�
//thing�� update()
	//����� ������ �������� �𸥴�
