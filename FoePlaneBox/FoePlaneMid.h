#pragma once
#include"FoePlane.h"

class CFoePlaneMid :public CFoePlane {

public:
	virtual void InitFoePlane() override;
	virtual void ShowFoePlane() override;
	//���˷ɻ���ײ��ҷɻ�
	virtual bool IsHitPlayer(CPlayer&) override;
	//ײ�����˷ɻ�
	virtual bool IsHitGunner(CGunner*) override;
};