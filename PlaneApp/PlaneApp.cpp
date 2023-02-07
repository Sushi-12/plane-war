#include"PlaneApp.h"
#include"../Config/Config.h"
#include"../Player/Player.h"
#include"../GameFrame/GameFrame.h"
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"


CREATE_OBJECT(CPlaneApp)
WINDOWS_PARAM(600 + 16, 800 + 39, 400, 100, L"飞机大战");


CPlaneApp::CPlaneApp():m_score(0) {

}
CPlaneApp::~CPlaneApp() {
}

void CPlaneApp::Init() {
	//初始化背景
	m_back.InitBack();

	//初始化玩家飞机
	m_player.InitPlayer();

	//加载分数板
	::loadimage(&m_board, L"./res/cardboard.png",200,50);

	//设定所有的定时器
	SetTimer();
} 

void CPlaneApp::Paint() {
	//显示背景
	m_back.ShowBack();

	//显示玩家飞机
	m_player.ShowPlayer();
	//显示所有的炮弹
	m_gunBox.ShowAllGunner();
	//显示所有正常的敌人飞机
	m_foeBox.ShowAllFoe();

	//显示爆炸效果
	m_foeBox.ShowA11FoeBoom();

	//显示分数
	ShowScore();
}

void CPlaneApp::Close(WPARAM w, LPARAM l) {
}

void CPlaneApp::SetTimer() {
	// win API 设定定时器
	::SetTimer(m_hWnd,	//窗口句柄
		BACK_MOVE_TIMEID,//定时器的ID(用于区分和标识各个定时器)
		BACK_MOVE_INTERVAL,//触发的频率间隔
	nullptr);	//定时器触发的时候，调用的函数

	//用于定时检测是否按下方向键
	::SetTimer(m_hWnd,PLAYER_MOVE_TIMEID,PLAYER_MOVE_INTERVAL,nullptr);

	//炮弹定时移动
	::SetTimer(m_hWnd, GUNNER_MOVE_TIMEID, GUNNER_MOVE_INTERVAL, nullptr);

	//定时发射炮弹
	::SetTimer(m_hWnd, GUNNER_SEND_TIMEID, GUNNER_SEND_INTERVAL, nullptr);
	
	//敌人飞机定时移动
	::SetTimer(m_hWnd, FOE_MOVE_TIMEID, FOE_MOVE_INTERVAL, nullptr);

	//创建三种敌人飞机
	::SetTimer(m_hWnd, FOEBIG_CREATE_TIMEID, FOEBIG_CREATE_INTERVAL, nullptr);
	::SetTimer(m_hWnd, FOEMID_CREATE_TIMEID, FOEMID_CREATE_INTERVAL, nullptr);
	::SetTimer(m_hWnd, FOESMA_CREATE_TIMEID, FOESMA_CREATE_INTERVAL, nullptr);
	
	//定时检测是否碰撞
	::SetTimer(m_hWnd, CHECK_HIT_TIMEID, CHECK_HIT_INTERVAL, nullptr);

	//定时切换敌人飞机爆炸效果
	::SetTimer(m_hWnd, SHOW_BOOM_TIMEID, SHOW_BOOM_INTERVAL, nullptr);

}

void CPlaneApp::ON_WM_TIMER(WPARAM w, LPARAM l) {
	switch (w)
	{
	case BACK_MOVE_TIMEID:   //如果是背景移动的定时器
	{
		m_back.MoveBack(BACK_MOVE_STEP);
	}
	break;

	case PLAYER_MOVE_TIMEID:   //如果是定时监测方向键
	{
		if (::GetAsyncKeyState(VK_UP)) {			//判断方向键up是否按下
			m_player.MovePlayer(VK_UP, PLAYER_MOVE_STEP);
		}
		if (::GetAsyncKeyState(VK_DOWN))
		{
			m_player.MovePlayer(VK_DOWN, PLAYER_MOVE_STEP);
		}
		if (::GetAsyncKeyState(VK_LEFT))
		{
			m_player.MovePlayer(VK_LEFT, PLAYER_MOVE_STEP);
		}
		if (::GetAsyncKeyState(VK_RIGHT))
		{
			m_player.MovePlayer(VK_RIGHT, PLAYER_MOVE_STEP);
		}
	}
		break;
	case GUNNER_MOVE_TIMEID:
	{
		m_gunBox.MoveAllGunner(GUNNER_MOVE_STEP);
	}
	break;
	case GUNNER_SEND_TIMEID:
	{
		//定时发射炮弹且放到炮弹盒子链表中
		m_gunBox.m_lstGun.push_back(m_player.SendGunner());
	}
	break;
	case FOE_MOVE_TIMEID:
	{
		m_foeBox.MoveAllFoe();
	}
	break;

#define CREATE_FOE(FOE_CLASS)\
	CFoePlane* pFoe = new FOE_CLASS;\
	pFoe->InitFoePlane();\
	m_foeBox.m_lstFoe.push_back(pFoe);

	case FOEBIG_CREATE_TIMEID:
	{
		//CFoePlane* pFoe = new CFoePlaneBig;
		//pFoe->InitFoePlane();
		//m_foeBox.m_lstFoe.push_back(pFoe);
		CREATE_FOE(CFoePlaneBig)
	}
	break;
	case FOEMID_CREATE_TIMEID:
	{
		CREATE_FOE(CFoePlaneMid)
	}
	break;
	case FOESMA_CREATE_TIMEID:
	{
		CREATE_FOE(CFoePlaneSma)
	}
	break;
#undef CREATE_FOE
	case CHECK_HIT_TIMEID: {
		bool isBoom = false;
		list<CFoePlane*>::iterator iteFoe = m_foeBox.m_lstFoe.begin();
		while (iteFoe != m_foeBox.m_lstFoe.end()){
			isBoom = false;//每次循环认为没爆炸

		//判断是否撞击玩家飞机
			if ((*iteFoe)->IsHitPlayer(m_player)){
				GameOver();
				::MessageBox(m_hWnd, L"GameOver",L"提示",MB_OK);

				//投递消息
				::PostMessage(m_hWnd,//给谁发消息
					WM_CLOSE,//送什么消息
					NULL,NULL);//消息携带的参数
				return;
			}

			//判断炮弹的链表，判断每一个
			list<CGunner*>::iterator iteGun = m_gunBox.m_lstGun.begin();
			while (iteGun != m_gunBox.m_lstGun.end()){	
				//判断是否碰撞炮弹
				if (*iteGun && (*iteFoe)->IsHitGunner(*iteGun)) {
					delete(* iteGun);	//删除炮弹
					(*iteGun) = nullptr;
					iteGun = m_gunBox.m_lstGun.erase(iteGun);	//删除炮弹节点
					//敌人飞机掉血
					(*iteFoe)->m_blood -= GUNNER_HURT;
					if ((*iteFoe)->m_blood <= 0) {//要爆炸了
						++m_score;//加分


						m_foeBox.m_lstFoeBoom.push_back(*iteFoe);	//添加到爆炸的链表中
						iteFoe= m_foeBox.m_lstFoe.erase(iteFoe);	//删除正常链表的节点
						isBoom = true;
						break;
					}
					continue;
				}
				iteGun++;	
			}
			if (!isBoom) { iteFoe++;}	//如果没爆炸，++
		}
	}
	 break;
	case SHOW_BOOM_TIMEID: {
		list<CFoePlane*>::iterator ite = m_foeBox.m_lstFoeBoom.begin();
		while (ite!= m_foeBox.m_lstFoeBoom.end()){
			if (*ite) {
				if ((--(*ite)->m_showId) <= 0) {
					delete(*ite);//爆炸效果显示完毕，删除敌人飞机
					(*ite) = nullptr;
					ite=m_foeBox.m_lstFoeBoom.erase(ite);//删除爆炸链表节点
					continue;
				}

			}


			ite++;
		}
	}
	break;
	}
}



	void  CPlaneApp::ON_WM_KEYDOWN(WPARAM vk) {
		//m_player.MovePlayer(vk, PLAYER_MOVE_STEP);
	}


	void  CPlaneApp::GameOver() {

		//停止计时器
		::KillTimer(m_hWnd, BACK_MOVE_TIMEID);
		//用于定时检测是否按下方向键
		::KillTimer(m_hWnd, PLAYER_MOVE_TIMEID);
		::KillTimer(m_hWnd, GUNNER_MOVE_TIMEID);
		::KillTimer(m_hWnd, GUNNER_SEND_TIMEID);
		::KillTimer(m_hWnd, FOE_MOVE_TIMEID);
		::KillTimer(m_hWnd, FOEBIG_CREATE_TIMEID);
		::KillTimer(m_hWnd, FOEMID_CREATE_TIMEID);
		::KillTimer(m_hWnd, FOESMA_CREATE_TIMEID);
		::KillTimer(m_hWnd, CHECK_HIT_TIMEID);
		::KillTimer(m_hWnd, SHOW_BOOM_TIMEID);
	}


	void  CPlaneApp::ShowScore() {
		::putimage(0, 0, &m_board);//显示分数版

		
		TCHAR arr[5] = {0};
		_itot_s(m_score, arr, 10);
		wstring str = L"分数为：" ;
		str += arr;
		::settextcolor(RGB(255,0,0));		//改变文字颜色
		RECT rect{ 20,10,180,40 };
		//显示分数
		drawtext(str.c_str(),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	}