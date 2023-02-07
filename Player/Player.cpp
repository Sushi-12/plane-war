#include"Player.h"
#include"../Config/Config.h"


CPlayer::CPlayer(): m_x (0), m_y(0){}
CPlayer::~CPlayer() {}

void CPlayer::InitPlayer() {
	m_x = (BACK_WIDTH - PLAYER_WIDTH) / 2;
	m_y = BACK_HEIGHT - PLAYER_HEIGHT;

//加载原图和屏蔽图
	::loadimage(&m_player, L"./res/playerplane.jpg");
	::loadimage(&m_playerMask, L"./res/playerplane-mask.jpg");
}
void CPlayer::ShowPlayer() {
	::putimage(m_x, m_y, &m_playerMask, SRCPAINT);		//传输方式，SRCPAINT 位或
	::putimage(m_x, m_y, &m_player, SRCAND);			//传输方式，SRCAND 位与
}
void CPlayer::MovePlayer(int direct, int step) {
	if (direct == VK_UP) {
		if (m_y - step >= 0)
			m_y -= step;
		else m_y = 0;
	}
	else if (direct == VK_DOWN) {
		if (m_y + step <= (BACK_HEIGHT - PLAYER_HEIGHT))
			m_y += step;
		else m_y = (BACK_HEIGHT - PLAYER_HEIGHT);
	}
	else if (direct == VK_LEFT) {
		if (m_x - step >= 0)
			m_x -= step;
		else m_x = 0;
	}
	else if (direct == VK_RIGHT) {
		if (m_x + step <= (BACK_WIDTH - PLAYER_WIDTH))
			m_x += step;
		else m_x = (BACK_WIDTH - PLAYER_WIDTH);
	}

}



CGunner* CPlayer::SendGunner() {
	CGunner* pGun = new CGunner;
	int x = m_x+ (PLAYER_WIDTH-GUNNER_WIDTH)/2;
	int y = m_y - GUNNER_HEIGHT;
	pGun->InitGunner(x,y);

	return pGun;
}