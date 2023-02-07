#include"FoePlaneMid.h"
#include"../Config/Config.h"

void CFoePlaneMid::InitFoePlane() {
	::loadimage(&m_foe, L"./res/foeplanemid.jpg");
	m_x = rd() % (BACK_WIDTH - FOE_MID_WIDTH + 1);
	m_y = -FOE_MID_HEIGHT;
	m_blood = MID_BOLOOD;
	m_showId = 3;
}
void CFoePlaneMid::ShowFoePlane() {
	//����ʾ����ͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_MID_WIDTH, FOE_MID_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		FOE_MID_WIDTH, (3 - m_showId) * FOE_MID_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCPAINT);

	//��ʾԭͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_MID_WIDTH, FOE_MID_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		0, (3 - m_showId) * FOE_MID_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCAND);
}
//���˷ɻ���ײ��ҷɻ�
bool CFoePlaneMid::IsHitPlayer(CPlayer& player) {
	int x1 = player.m_x + PLAYER_WIDTH / 2;
	if (m_x <= x1 <= m_x + FOE_MID_WIDTH && m_y <= player.m_y <= (m_y + FOE_MID_HEIGHT)) {
		return true;
	}


	int y1 = player.m_y + PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= (m_y + FOE_MID_WIDTH) && m_y <= y1 && y1 <= (m_y + FOE_MID_HEIGHT)) {
		return true;
	}

	int x2 = player.m_x + PLAYER_WIDTH;
	if (m_x <= x2 && x2 <= (m_y + FOE_MID_WIDTH) && m_y <= y1 && y1 <= (m_y + FOE_MID_HEIGHT)) {
		return true;
	}
	return false;
}
//ײ�����˷ɻ�
bool CFoePlaneMid::IsHitGunner(CGunner* pgun) {
	int x = pgun->m_x + GUNNER_WIDTH / 2;
	if (m_x <= x && x <= (m_x + FOE_MID_WIDTH)) {
		return true;
	}

	return false;
}