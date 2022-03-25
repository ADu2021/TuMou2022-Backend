#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef MAP_H
#define MAP_H

#include "Player.h"
#include<string.h>
#include<vector>
#include <cstdlib>
#include <cmath>

const int TURN_COUNT = 36 * 4;//�غ���
const int MAP_SIZE = 50;//��ͼ�ı߳�
const int MINE_NUM = 100;

const int oo = 2e9;

enum Sign { RED, BLUE, TIE };//�����������/��
enum direction { N, NE, SE, S, SW, NW };//����:

const int dx[6] = { 1, 1, 0, -1, -1, 0 }, dy[6] = { 0, -1, -1, 0, 1, 1 }, dz[6] = { -1, 0, 1, 1, 0, -1 };

class Point
{//�������
public:
	int x;
	int y;
	int z;
	int MineIdx = -1;	//��Դ�����ţ�-1����û����Դ��
	int BarrierIdx = 0;	//�ϰ������ţ�-1����û���ϰ���
	int PlayerIdx = -1;	   //��ҵı�ţ�-1����û����ң� 0�췽��1����
	bool isvalid = 0;				//�Ƿ��ڵ�ͼ��

	Point(const int _x = -1000, const int _y = -1000, const int _z = -1000, const int _mineindex = -1, const int _barrieridx = -1, const bool isvalid = 0) {
		x = _x;
		y = _y;
		z = _z;
		MineIdx = _mineindex;
		BarrierIdx = _barrieridx;
	}
};


class Mine {	//��Դ��
public:
	//int weight, available, belong, initheight;
	Coordinate pos;
	int num, belong = 0;   //belong=0Ϊ����,-1������1�췽
	bool available = 1;
	Mine(const int n, Coordinate x) { num = n; pos = x; }
};



struct Coordinate
{
	int x, y, z;
	Coordinate() { x = 0, y = 0, z = 0; }
	Coordinate(int a, int b, int c) { x = a, y = b, z = c; }

	bool operator==(Coordinate t)
	{
		if (this->x == t.x && this->y == t.y && this->z == t.z)
		{
			return true;
		}
		return false;
	}
};


class Map {
public:
	Point data[2 * MAP_SIZE - 1][2 * MAP_SIZE - 1][2 * MAP_SIZE - 1];		//��ͼ��Ϣ��data[i][j][k]��ʾ��ͼһ��λ�õ���Ϣ

	std::vector <Mine> mine;
	std::vector<Coordinate> barrier;
	std::vector<Player> enemy_unit;
	int nowSize = MAP_SIZE;			//��ǰ��Ȧ�ı߳�
	int viewSize = MAP_SIZE;
	int mine_num = 0;
	int barrier_num = 0;
	int enemy_num = 0;


	Map()		//��ʼ����ͼ
	{
		mine_num = 0;
		barrier_num = 0;
		enemy_num = 0;
		unsigned seed;
		srand(seed);
		for (int i = 0; i < 2 * MAP_SIZE - 1; i++)
			for (int j = 0; j < 2 * MAP_SIZE - 1; j++)
				for (int k = 0; k < 2 * MAP_SIZE - 1; k++) {
					if (isValid(i, j, k))
					{
						//����ж��Ƿ�����Դ�㡢�ϰ���
						int mineidx = -1;
						int barrieridx = -1;
						if (rand() % 10 == 1) { mineidx = mine_num; }				//ʮ��֮һ���ʣ� TO DO���޸���ֵ
						else if (rand() % 10 == 2) { barrieridx = barrier_num; }	//ʮ��֮һ���ʣ� TO DO���޸���ֵ

						if (isValid(i, j, k))
						{
							data[i][j][k] = Point(i, j, k, mineidx, barrieridx, 1);
							if (mineidx >= 0)
							{
								mine.push_back(Mine(MINE_NUM, Coordinate(i, j, k)));
								mine_num++;
							}
							if (barrieridx >= 0)
							{
								barrier.push_back(Coordinate(i, j, k));
								barrier_num++;
							}
						}


					}
				}
	}


	Map(Map totalmap, const Player& p)			//�������p����Ұ��ͼ,���ݸ�ѡ��		
	{
		*this = totalmap;
		viewSize = p.sight_range;
		for (auto i : totalmap.mine)
		{

			if (getDistance(p.pos, i.pos) <= viewSize - 1)
			{
				mine.push_back(i);
				data[i.pos.x][i.pos.y][i.pos.z].MineIdx = mine_num++;
			}
		}
		for (auto i : totalmap.barrier)
		{
			if (getDistance(p.pos, i) <= viewSize - 1)
			{
				barrier.push_back(i);
				data[i.x][i.y][i.z].BarrierIdx = barrier_num++;
			}
		}
		for (auto i : totalmap.enemy_unit)
		{
			if (getDistance(p.pos, i.pos) <= viewSize - 1)
			{
				enemy_unit.push_back(i);
				data[i.pos.x][i.pos.y][i.pos.z].PlayerIdx = i.id;
				enemy_num++;
			}
		}
	}


	bool isValid(int x, int y, int z)		//�ж�ĳ�������Ƿ��ڵ�ͼ�� 
	{
		if (x >= 0 && x <= 2 * MAP_SIZE - 1 && y >= 0 && y <= 2 * MAP_SIZE - 1 && z >= 0 && z <= 2 * MAP_SIZE - 1)
		{
			if ((x + y + z) == (3 * MAP_SIZE - 3))
				return true;
			else
				return false;
		}
		else
			return false;
	}

	Point operator [] (const Coordinate& c) { return data[c.x][c.y][c.z]; }

	bool isValid(Coordinate c)				//�ж�ĳ�������Ƿ��ڵ�ͼ��  
	{
		return isValid(c.x, c.y, c.z);
	}



	int getDistance(Coordinate a, Coordinate b)		//������������֮��ľ��� 
	{
		return (abs(a.x - b.x), abs(a.y - b.y), abs(a.z - b.z)) / 2;
	}

};

#endif