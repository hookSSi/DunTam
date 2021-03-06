#pragma once
#include "BehaviorTree.h"
#include "PathFinding.h"

using namespace std;

namespace AI
{
	DIRECTION_TYPE VectorToDirection(int x1, int y1, int x2, int y2);
	bool IsDirect(int x1, int y1, int x2, int y2);

	class CheckStatus: public Node
	{
	private:
		int m_status;
	public:
		CheckStatus(int p_status) : m_status(p_status){}
		virtual bool Run() override
		{
			if (m_status == 0)
			{
				return true;
			}	
			else
			{
				return false;
			}		
		}
	};
	class Detect : public Node
	{
	private:
		EnemyC* m_this;
	public:
		Detect(EnemyC *p_this) : m_this(p_this) {}
		virtual bool Run() override
		{
			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			if (m_this->IsAttacked() || (m_this->GetRange() >= Distance(targetX, targetY, x, y)))
			{
				if (m_this->IsAttacked())
					m_this->SetRange(100);
				if ((m_this->GetRange() >= Distance(targetX, targetY, x, y)))
					m_this->SetRange(m_this->GetRange() + 5);
				return true;
			}
			else
			{
				m_this->Move((DIRECTION_TYPE)random(4));
				return false;
			}
		}
	};
	class SearchingWay : public Node
	{
	private:
		Object* m_this;
		int m_range;
	public:
		SearchingWay(Object* p_this,int p_range) : m_this(p_this), m_range(p_range){}
		virtual bool Run() override
		{
			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			if (m_range >= Distance(targetX, targetY, x, y))
			{
				Astar(MAP, targetX, targetY, x, y);
				return true;
			}
			else
			{
				return false;
			}		
		}
	};
	class SearchingWay_teleporter : public Node
	{
	private:
		int m_x, m_y;
		int m_range;
	public:
		SearchingWay_teleporter(int p_x, int p_y, int p_range) : m_x(p_x), m_y(p_y), m_range(p_range) {}
		virtual bool Run() override
		{
			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			if (m_range > Distance(targetX, targetY, m_x, m_y))
			{
				Astar_Telepoter(MAP, targetX, targetY, m_x, m_y);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	class Move : public Node
	{
	private:
		Object* m_this;
	public:
		Move(Object* p_this) : m_this(p_this) {}
		virtual bool Run()
		{
			int lastX, lastY;
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();
			DIRECTION_TYPE dir;

			lastX = MAP.Get(x, y).m_lastX;
			lastY = MAP.Get(x, y).m_lastY;

			// 얻은 좌표를 방향으로 변환
			if (lastX > x)
				dir = RIGHT;
			else if (lastX < x)
				dir = LEFT;
			else if (lastY > y)
				dir = DOWN;
			else if (lastY < y)
				dir = UP;

			if (!m_this->IsWall(dir))
			{
				m_this->Move(dir);
				return true;
			}	
			else
			{
				return false;
			}
		}
	};
	class Attack : public Node
	{
	private:
		EnemyC* m_this;
		int m_range;
		DIRECTION_TYPE dir;
	public:
		Attack(EnemyC* p_this,int p_range) : m_this(p_this),m_range(p_range) {}
		virtual bool Run() override
		{
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			if (Distance(x,y,targetX,targetY) <= m_range && IsDirect(x,y,targetX,targetY))
			{
				dir = VectorToDirection(x, y, targetX, targetY);
				m_this->Attack(dir);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	class Attack_Dynamic : public Node
	{
	private:
		EnemyC* m_this;
		int m_range;
		DIRECTION_TYPE dir;
	public:
		Attack_Dynamic(EnemyC* p_this, int p_range) : m_this(p_this), m_range(p_range) {}
		virtual bool Run() override
		{
			int x = m_this->GetPositionX();
			int y = m_this->GetPositionY();

			int targetX = GameManager::GetInstance()->player->GetPositionX();
			int targetY = GameManager::GetInstance()->player->GetPositionY();

			int lastX = MAP.Get(x, y).m_lastX;
			int lastY = MAP.Get(x, y).m_lastY;

			if (Distance(x, y, targetX, targetY) <= m_range && IsDirect(x, y, targetX, targetY))
			{
				dir = VectorToDirection(x, y, targetX, targetY);
				m_this->Attack(dir);
				dir = VectorToDirection(x, y, lastX, lastY);
				m_this->Move(dir);

				return true;
			}
			else
			{
				return false;
			}
		}
	};
	class ChargingAttak : public Node
	{
	private:
		Boss* m_this;
		int m_maxFury;
	public:
		ChargingAttak(Boss* p_this,int p_maxFury) : m_this(p_this),m_maxFury(p_maxFury) {}
		virtual bool Run() override
		{
			int fury = m_this->GetFury();

			if (fury > m_maxFury)
			{
				m_this->SetFury(0);
				return true;
			}
			else
			{
				m_this->SetFury(fury + 1);
				return false;
			}
		}
	};
	DIRECTION_TYPE VectorToDirection(int x1, int y1, int x2, int y2) // 방향 반환
	{
		DIRECTION_TYPE dir;

		if (x2 > x1)
			dir = RIGHT;
		else if (x2 < x1)
			dir = LEFT;
		else if (y2 > y1)
			dir = DOWN;
		else if (y2 < y1)
			dir = UP;
		return dir;
	}
	bool IsDirect(int x1, int y1, int x2, int y2)
	{
		bool isDirect = false;

		if (x2 > x1)
			isDirect = !isDirect;
		else if (x2 < x1)
			isDirect = !isDirect;
		if (y2 > y1)
			isDirect = !isDirect;
		else if (y2 < y1)
			isDirect = !isDirect;

			return isDirect;
	}
}