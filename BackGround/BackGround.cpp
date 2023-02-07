#include"BackGround.h"
#include"../Config/Config.h"  


CBackGround::CBackGround() {
	m_x=0;
	m_y=0;
	m_back;
}
CBackGround::~CBackGround() {}
void CBackGround::InitBack() {
	::loadimage(&m_back,_T("./res/背景.jpg"));  //相对路径，相对于工程文件
	m_x = 0;
	m_y = -BACK_HEIGHT;
}
void CBackGround::ShowBack() {
	::putimage(m_x, m_y, &m_back);
}
void CBackGround::MoveBack(int step) {
	m_y += step;
	if (m_y >= 0) {
		m_y = -BACK_HEIGHT;
	}
}