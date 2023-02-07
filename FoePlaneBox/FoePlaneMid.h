#pragma once
#include"FoePlane.h"

class CFoePlaneMid :public CFoePlane {

public:
	virtual void InitFoePlane() override;
	virtual void ShowFoePlane() override;
	//敌人飞机碰撞玩家飞机
	virtual bool IsHitPlayer(CPlayer&) override;
	//撞击敌人飞机
	virtual bool IsHitGunner(CGunner*) override;
};