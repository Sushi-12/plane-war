#pragma once
#include<easyx.h>
#include"../GunnerBox/Gunner.h"

class CPlayer {
public:
	IMAGE m_player;
	IMAGE m_playerMask;
	int m_x;
	int m_y;
public:
	CPlayer();
	~CPlayer();
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(int direct, int step);
	CGunner* SendGunner();
};