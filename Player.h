#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef PLAYER_H
#define PLAYER_H

#include"Map.h"

class Player
{
public:
	int id;

	Coordinate pos;

	int attack_range;   //������Χ
	int sight_range; //��Ұ��Χ
	int move_range; //�ƶ���Χ
	int mine_speed; //�ɼ��ٶ�

	int at; //������
	int hp; //Ѫ��

	int mines;  // �ɼ�������Դ

	Player(int _id) : id(_id), attack_range(1), sight_range(6), move_range(1), mine_speed(10),
		at(10), hp(100),mines(0) {};  //pos at (0,0,0)

	Player(int _id, int x, int y, int z) : id(_id), attack_range(1), sight_range(6), move_range(1), mine_speed(10),
		at(10), hp(100), mines(0), pos(Coordinate(x,y,z)) {};  //pos at (0,0,0)
	Player(int _id, Coordinate c) : id(_id), attack_range(1), sight_range(6), move_range(1), mine_speed(10),
		at(10), hp(100), mines(0), pos(c) {};  //pos at (0,0,0)

	// todo : ���ڳ�ʼ������

};


#endif