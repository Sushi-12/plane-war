#include"GunnerBox.h"
#include"../Config/Config.h"

CGunnerBox::CGunnerBox() {}
CGunnerBox::~CGunnerBox() {
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end())
	{
		if (*ite) {//判断节点中的炮弹指针是否为空
			delete(*ite);//删除炮弹
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();//清空节点
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

			//判断是否出界，出界需要delete
			if ((*ite)->m_y<=-GUNNER_HEIGHT) {
				delete(*ite);//删除炮弹
				(*ite) = nullptr;
				ite=m_lstGun.erase(ite);		//删除节点,自带++效果
				continue;
			}
		}
		 ite++;
	}
}