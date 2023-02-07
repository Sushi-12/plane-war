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
	//先显示屏蔽图
	::putimage(m_x, m_y,//显示到目标窗口的位置
		GUNNER_WIDTH, GUNNER_HEIGHT,//显示的高度和宽度
		&m_gunner,
		GUNNER_WIDTH,0,//从源图的那个位置显示
		SRCPAINT);

	//显示原图
	::putimage(m_x, m_y,//显示到目标窗口的位置
		GUNNER_WIDTH, GUNNER_HEIGHT,//显示的高度和宽度
		&m_gunner,
		0, 0,//从源图的那个位置显示
		SRCAND);



	}
void CGunner::MoveGunner(int step) {
	m_y -= step;
	}