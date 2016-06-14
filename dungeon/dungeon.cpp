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
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)	//���� ����(�ʻ���) ���ӻ���(������)
			{
				randomize();
				gameManager->GameSetting(0);
				gameManager->SetGameState(GAMING);
			}
			else if (GetAsyncKeyState(0x44) == (short)0x8001)
			{
				randomize();
				gameManager->GameSetting(1);
				gameManager->SetGameState(GAMING);
			}
		}

		if(gameManager->gameState == GAMING/*���� ������*/)
		{

			gameManager->ObjectUpdate();	//������Ʈ ������Ʈ

			gameManager->ObjectDraw();	//������Ʈ �׸���

			gameManager->PrintPlayerState();	//�÷��̾� ���� ���

			//Ű���� �̺�Ʈ
			gameManager->KeyEvent();
			//���� ���� �׸���

			//�ɺ�ȯ
			DIRECTION_TYPE dir = gameManager->IsMapChange();

			if (dir != NONE)
			{
				if (gameManager->map[gameManager->nowMapY][gameManager->nowMapX]->IsDoor(dir))
				{
					gameManager->ChangeMap(dir);//�ʺ�ȯ
					Sleep(300);					//��� ����� (0.5��)
				}
			}
			//�÷��̾� �����
			if (gameManager->player->isDie)
			{
				delete gameManager->player;
				gameManager->SetGameState(GAMEOVER);
			}

		}

		if (gameManager->gameState == PAUSE/*�Ͻ� ����*/)
		{
			//�Ͻ� ���� ȭ�� ���
			gameManager->DrawPausePage();
			//Ű �̺�Ʈ Ȯ�� �ϰ� ������ �ٽ� �������� �ƴϸ� ��� ����
			if (GetAsyncKeyState(0x50) == (short)0x8001)
			{
				gameManager->ObjectDrawCountZero();
				gameManager->SetGameState(GAMING);
			}

		}


		if (gameManager->gameState == GAMEOVER/*���� ����*/)
		{
			//���ӿ��� ȭ�� ���
			gameManager->DrawGameOverPage();

			//�׸��� �ٽ� ���� ����ȭ�� true
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)
			{
				gameManager->ClearRoom();
				gameManager->SetGameState(STARTMENU);
			}
		}

		if (gameManager->gameState == GAMECLEAR/*���� ����*/)
		{
			//���ӿ��� ȭ�� ���
			gameManager->DrawGameClearPage();

			//�׸��� �ٽ� ���� ����ȭ�� true
			if (GetAsyncKeyState(VK_SPACE) == (short)0x8001)
			{
				delete gameManager->player;
				gameManager->ClearRoom();
				gameManager->SetGameState(STARTMENU);
			}
		}


		int wait = (1000/FRAME) - (GetTickCount() - start);
		if(wait >= 0)
			Sleep(wait);
		count++;
		if (timer != time(NULL))
		{
			gotoxy(0, 0);
			printf("FPS : %d",count);
			count = 0;
			timer = time(NULL);
		}
	}
	//================================================================================������ ����
	return 0;
}

//bullet�� update()
	//�̵��� �����ϸ� �̵����ش�
//block�� update()
	//������ �ִ´�
//thing�� update()
	//����� ������ �������� �𸥴�
