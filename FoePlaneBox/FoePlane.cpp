#include"FoePlane.h"

//�����ҳ�ʼ��
std::random_device CFoePlane::rd;


CFoePlane::CFoePlane() {
	m_x=0;
	m_y=0;
	m_blood=0;
	m_showId=0;
}
CFoePlane::~CFoePlane() {}



void CFoePlane::MoveFoePlane(int step) {
	m_y += step;
}