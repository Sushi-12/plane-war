#include"Gunner.h"
#include"../Config/Config.h"

CGunner::CGunner():m_x(0), m_y(0){}
CGunner::~CGunner() {}
void CGunner::InitGunner(int x, int y) {
	m_x = x;
	m_y = y;

	::loadimage(&m_gunner, L"./res/gunner.jpg");
	}
void CGunner::ShowGunner() {
	//����ʾ����ͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		GUNNER_WIDTH, GUNNER_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_gunner,
		GUNNER_WIDTH,0,//��Դͼ���Ǹ�λ����ʾ
		SRCPAINT);

	//��ʾԭͼ
	::putimage(m_x, m_y,//��ʾ��Ŀ�괰�ڵ�λ��
		GUNNER_WIDTH, GUNNER_HEIGHT,//��ʾ�ĸ߶ȺͿ��
		&m_gunner,
		0, 0,//��Դͼ���Ǹ�λ����ʾ
		SRCAND);



	}
void CGunner::MoveGunner(int step) {
	m_y -= step;
	}