#include"FoePlaneBig.h"
#include"../Config/Config.h"

void CFoePlaneBig::InitFoePlane() {
	::loadimage(&m_foe, L"./res/foeplanebig.jpg");
	m_x=rd()%(BACK_WIDTH- FOE_BIG_WIDTH+1);
	m_y=-FOE_BIG_HEIGHT;
	m_blood= BIG_BOLOOD;
	m_showId=4;
 }
void CFoePlaneBig::ShowFoePlane() {
	//����ʾ����ͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_BIG_WIDTH, FOE_BIG_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		FOE_BIG_WIDTH, (4-m_showId)* FOE_BIG_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCPAINT);

	//��ʾԭͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		FOE_BIG_WIDTH, FOE_BIG_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_foe,
		0, (4 - m_showId) * FOE_BIG_HEIGHT,//��Դͼ���Ǹ�λ����ʾ
		SRCAND);
 }
//���˷ɻ���ײ��ҷɻ�
bool CFoePlaneBig::IsHitPlayer(CPlayer& player) {
	int x1 = player.m_x + PLAYER_WIDTH / 2;
	if (m_x <= x1 <= m_x + FOE_BIG_WIDTH && m_y <= player.m_y <= (m_y + FOE_BIG_HEIGHT)) {
		return true;
	}


	int y1 = player.m_y + PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= (m_y + FOE_BIG_WIDTH)  && m_y<=y1 && y1<=(m_y+ FOE_BIG_HEIGHT)) {
		return true;
	}

	int x2 = player.m_x + PLAYER_WIDTH;
	if (m_x <= x2 && x2 <= (m_y + FOE_BIG_WIDTH) && m_y <= y1 && y1 <= (m_y + FOE_BIG_HEIGHT)) {
		return true;
	}

	return false;
 }
//ײ�����˷ɻ�
bool CFoePlaneBig::IsHitGunner(CGunner* pgun) {
	int x = pgun->m_x + GUNNER_WIDTH / 2;
	if (m_x <= x && x <= (m_x + FOE_BIG_WIDTH)) {
		return true;
	}
	return false;
 }