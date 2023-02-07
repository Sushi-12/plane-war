#include"FoePlaneSma.h"
#include"../Config/Config.h"

void CFoePlaneSma::InitFoePlane() {
	::loadimage(&m_foe, L"./res/foeplanesma.jpg");
	m_x = rd() % (BACK_WIDTH - FOE_SMA_WIDTH + 1);
	m_y = -FOE_SMA_HEIGHT;
	m_blood = SMA_BOLOOD;
	m_showId = 2;
}
void CFoePlaneSma::ShowFoePlane() {
	//����ʾ����ͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_SMA_WIDTH, FOE_SMA_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		FOE_SMA_WIDTH, (2 - m_showId) * FOE_SMA_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCPAINT);

	//��ʾԭͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_SMA_WIDTH, FOE_SMA_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		0, (2 - m_showId) * FOE_SMA_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCAND);
}
//���˷ɻ���ײ��ҷɻ�
bool CFoePlaneSma::IsHitPlayer(CPlayer& player) {
	int x1 = player.m_x + PLAYER_WIDTH / 2;
	if (m_x <= x1 <= m_x + FOE_SMA_WIDTH && m_y <= player.m_y <= (m_y + FOE_SMA_HEIGHT)) {
		return true;
	}


	int y1 = player.m_y + PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= (m_y + FOE_SMA_WIDTH) && m_y <= y1 && y1 <= (m_y + FOE_SMA_HEIGHT)) {
		return true;
	}

	int x2 = player.m_x + PLAYER_WIDTH;
	if (m_x <= x2 && x2 <= (m_y + FOE_SMA_WIDTH) && m_y <= y1 && y1 <= (m_y + FOE_SMA_HEIGHT)) {
		return true;
	}
	return false;
}
//ײ�����˷ɻ�
bool CFoePlaneSma::IsHitGunner(CGunner*pgun) {
	int x = pgun->m_x + GUNNER_WIDTH / 2;
	if (m_x <= x && x <= (m_x + FOE_SMA_WIDTH)) {
		return true;
	}
	return false;
}