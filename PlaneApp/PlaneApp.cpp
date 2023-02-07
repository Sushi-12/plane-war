#include"PlaneApp.h"
#include"../Config/Config.h"
#include"../Player/Player.h"
#include"../GameFrame/GameFrame.h"
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"


CREATE_OBJECT(CPlaneApp)
WINDOWS_PARAM(600 + 16, 800 + 39, 400, 100, L"�ɻ���ս");


CPlaneApp::CPlaneApp():m_score(0) {

}
CPlaneApp::~CPlaneApp() {
}

void CPlaneApp::Init() {
	//��ʼ������
	m_back.InitBack();

	//��ʼ����ҷɻ�
	m_player.InitPlayer();

	//���ط�����
	::loadimage(&m_board, L"./res/cardboard.png",200,50);

	//�趨���еĶ�ʱ��
	SetTimer();
} 

void CPlaneApp::Paint() {
	//��ʾ����
	m_back.ShowBack();

	//��ʾ��ҷɻ�
	m_player.ShowPlayer();
	//��ʾ���е��ڵ�
	m_gunBox.ShowAllGunner();
	//��ʾ���������ĵ��˷ɻ�
	m_foeBox.ShowAllFoe();

	//��ʾ��ըЧ��
	m_foeBox.ShowA11FoeBoom();

	//��ʾ����
	ShowScore();
}

void CPlaneApp::Close(WPARAM w, LPARAM l) {
}

void CPlaneApp::SetTimer() {
	// win API �趨��ʱ��
	::SetTimer(m_hWnd,	//���ھ��
		BACK_MOVE_TIMEID,//��ʱ����ID(�������ֺͱ�ʶ������ʱ��)
		BACK_MOVE_INTERVAL,//������Ƶ�ʼ��
	nullptr);	//��ʱ��������ʱ�򣬵��õĺ���

	//���ڶ�ʱ����Ƿ��·����
	::SetTimer(m_hWnd,PLAYER_MOVE_TIMEID,PLAYER_MOVE_INTERVAL,nullptr);

	//�ڵ���ʱ�ƶ�
	::SetTimer(m_hWnd, GUNNER_MOVE_TIMEID, GUNNER_MOVE_INTERVAL, nullptr);

	//��ʱ�����ڵ�
	::SetTimer(m_hWnd, GUNNER_SEND_TIMEID, GUNNER_SEND_INTERVAL, nullptr);
	
	//���˷ɻ���ʱ�ƶ�
	::SetTimer(m_hWnd, FOE_MOVE_TIMEID, FOE_MOVE_INTERVAL, nullptr);

	//�������ֵ��˷ɻ�
	::SetTimer(m_hWnd, FOEBIG_CREATE_TIMEID, FOEBIG_CREATE_INTERVAL, nullptr);
	::SetTimer(m_hWnd, FOEMID_CREATE_TIMEID, FOEMID_CREATE_INTERVAL, nullptr);
	::SetTimer(m_hWnd, FOESMA_CREATE_TIMEID, FOESMA_CREATE_INTERVAL, nullptr);
	
	//��ʱ����Ƿ���ײ
	::SetTimer(m_hWnd, CHECK_HIT_TIMEID, CHECK_HIT_INTERVAL, nullptr);

	//��ʱ�л����˷ɻ���ըЧ��
	::SetTimer(m_hWnd, SHOW_BOOM_TIMEID, SHOW_BOOM_INTERVAL, nullptr);

}

void CPlaneApp::ON_WM_TIMER(WPARAM w, LPARAM l) {
	switch (w)
	{
	case BACK_MOVE_TIMEID:   //����Ǳ����ƶ��Ķ�ʱ��
	{
		m_back.MoveBack(BACK_MOVE_STEP);
	}
	break;

	case PLAYER_MOVE_TIMEID:   //����Ƕ�ʱ��ⷽ���
	{
		if (::GetAsyncKeyState(VK_UP)) {			//�жϷ����up�Ƿ���
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
		//��ʱ�����ڵ��ҷŵ��ڵ�����������
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
			isBoom = false;//ÿ��ѭ����Ϊû��ը

		//�ж��Ƿ�ײ����ҷɻ�
			if ((*iteFoe)->IsHitPlayer(m_player)){
				GameOver();
				::MessageBox(m_hWnd, L"GameOver",L"��ʾ",MB_OK);

				//Ͷ����Ϣ
				::PostMessage(m_hWnd,//��˭����Ϣ
					WM_CLOSE,//��ʲô��Ϣ
					NULL,NULL);//��ϢЯ���Ĳ���
				return;
			}

			//�ж��ڵ��������ж�ÿһ��
			list<CGunner*>::iterator iteGun = m_gunBox.m_lstGun.begin();
			while (iteGun != m_gunBox.m_lstGun.end()){	
				//�ж��Ƿ���ײ�ڵ�
				if (*iteGun && (*iteFoe)->IsHitGunner(*iteGun)) {
					delete(* iteGun);	//ɾ���ڵ�
					(*iteGun) = nullptr;
					iteGun = m_gunBox.m_lstGun.erase(iteGun);	//ɾ���ڵ��ڵ�
					//���˷ɻ���Ѫ
					(*iteFoe)->m_blood -= GUNNER_HURT;
					if ((*iteFoe)->m_blood <= 0) {//Ҫ��ը��
						++m_score;//�ӷ�


						m_foeBox.m_lstFoeBoom.push_back(*iteFoe);	//��ӵ���ը��������
						iteFoe= m_foeBox.m_lstFoe.erase(iteFoe);	//ɾ����������Ľڵ�
						isBoom = true;
						break;
					}
					continue;
				}
				iteGun++;	
			}
			if (!isBoom) { iteFoe++;}	//���û��ը��++
		}
	}
	 break;
	case SHOW_BOOM_TIMEID: {
		list<CFoePlane*>::iterator ite = m_foeBox.m_lstFoeBoom.begin();
		while (ite!= m_foeBox.m_lstFoeBoom.end()){
			if (*ite) {
				if ((--(*ite)->m_showId) <= 0) {
					delete(*ite);//��ըЧ����ʾ��ϣ�ɾ�����˷ɻ�
					(*ite) = nullptr;
					ite=m_foeBox.m_lstFoeBoom.erase(ite);//ɾ����ը����ڵ�
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

		//ֹͣ��ʱ��
		::KillTimer(m_hWnd, BACK_MOVE_TIMEID);
		//���ڶ�ʱ����Ƿ��·����
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
		::putimage(0, 0, &m_board);//��ʾ������

		
		TCHAR arr[5] = {0};
		_itot_s(m_score, arr, 10);
		wstring str = L"����Ϊ��" ;
		str += arr;
		::settextcolor(RGB(255,0,0));		//�ı�������ɫ
		RECT rect{ 20,10,180,40 };
		//��ʾ����
		drawtext(str.c_str(),&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	}