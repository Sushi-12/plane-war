#include"GunnerBox.h"
#include"../Config/Config.h"

CGunnerBox::CGunnerBox() {}
CGunnerBox::~CGunnerBox() {
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end())
	{
		if (*ite) {//�жϽڵ��е��ڵ�ָ���Ƿ�Ϊ��
			delete(*ite);//ɾ���ڵ�
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();//��սڵ�
}
void CGunnerBox::ShowAllGunner() {
	for (CGunner* pGun : m_lstGun) {
		if (pGun)pGun->ShowGunner();
	}
}
void CGunnerBox::MoveAllGunner(int step) {
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			(*ite)->MoveGunner(step);

			//�ж��Ƿ���磬������Ҫdelete
			if ((*ite)->m_y<=-GUNNER_HEIGHT) {
				delete(*ite);//ɾ���ڵ�
				(*ite) = nullptr;
				ite=m_lstGun.erase(ite);		//ɾ���ڵ�,�Դ�++Ч��
				continue;
			}
		}
		 ite++;
	}
}