#pragma once
#include<math.h>
#include "Array2D.h"
#include "Heap_rand.h"
#include "GameManager.h"

	const int QUEUESIZE = 1024;
	const int DIRTABLE[4][2] = {
		{ 0, 1 }, // EAST
		{ 1, 0 }, // SOUTH
		{ 0, -1 },	// WEST
		{ -1, 0 }	// NORTH
	};
	const float DISTTABLE[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	class Coordinate // Ʈ���� ���� ��ü Ŭ����
	{
	public:
		int x;
		int y;
		float heuristic;
	};

	class Cell
	{
	public:
		bool m_marked = false;
		bool m_passable = true;
		float m_distance = 0;
		int m_lastX = -1;
		int m_lastY = -1;
		float m_weight = 0; // ���� ���� ���� ���� ���̶�� ���� ��
	};

	static Array2D<Cell> MAP;

	void ClearCells(Array2D<Cell>& MAP, int p_x, int p_y, int p_gx, int p_gy);
	float ComplexHeuristic(int x, int y, int targetX, int targetY, int dir);
	float Distance(int x1, int y1, int x2, int y2);
	void Astar(Array2D<Cell>& p_map, int p_x, int p_y, int p_gx, int p_gy);
	int CompareCoordinatesDescending(Coordinate left, Coordinate right);
