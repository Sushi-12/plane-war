#pragma once
#include<easyx.h>
#include"../Player/Player.h"
#include"../GunnerBox/Gunner.h"
#include<random>


class CFoePlane
{
public:
	IMAGE m_foe;
	int   m_x;
	int   m_y;
	int   m_blood;
	int   m_showId;

	static std::random_device rd;
public:
	CFoePlane();
	virtual ~CFoePlane();
	virtual void InitFoePlane()=0;
	virtual void ShowFoePlane()=0;
	void MoveFoePlane(int step);
	//���˷ɻ���ײ��ҷɻ�
	virtual bool IsHitPlayer(CPlayer&)=0;
	//ײ�����˷ɻ�
	virtual bool IsHitGunner(CGunner*)=0;
};

