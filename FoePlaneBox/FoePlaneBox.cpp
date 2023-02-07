#include"FoePlaneBox.h"
#include<typeinfo>
#include"FoePlaneBig.h"
#include"FoePlaneMid.h"
#include"FoePlaneSma.h"
#include"../Config/Config.h"

CFoePlaneBox::CFoePlaneBox() {

}


#define DELETE_FOE(LIST)\
	list<CFoePlane*>::iterator ite##LIST = LIST.begin();\
	while (ite##LIST != LIST.end()){\
		if ((*ite##LIST)){\
			delete(*ite##LIST);\
			(*ite##LIST) = nullptr;\
		}\
		ite##LIST++;\
	}\
	LIST.clear();

CFoePlaneBox::~CFoePlaneBox() {
	//list<CFoePlane*>::iterator ite = LIST.begin();
	//while (ite!=LIST.end())
	//{
	//	if ((*ite))
	//	{
	//		delete(*ite);	//删除敌人飞机
	//		(*ite) = nullptr;
	//	}
	//	ite++;
	//}
	//LIST.clear();//清空节点

	DELETE_FOE(m_lstFoe)
	DELETE_FOE(m_lstFoeBoom)
}
#undef DELETE_FOE


#define RANGE_FOELIST(LIST)\
	for (CFoePlane* pFoe : LIST) {\
if (pFoe) {\
	pFoe->ShowFoePlane();\
}\
	}


void CFoePlaneBox::ShowAllFoe() {
	//for (CFoePlane* pFoe : m_lstFoe) {//便利正常敌人飞机链表 ，显示
	//	if (pFoe) {
	//		pFoe->ShowFoePlane();
	//	}
	//}

	RANGE_FOELIST(m_lstFoe);
}
void CFoePlaneBox::ShowA11FoeBoom() {
	RANGE_FOELIST(m_lstFoeBoom);
}
#undef RANGE_FOELIST

void CFoePlaneBox::MoveAllFoe() {
	list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while (ite!= m_lstFoe.end()){
		if (*ite){
			//RTTI,Run Time Typy ID
			if (typeid(*(*ite)) == typeid(CFoePlaneBig)) {
				(*ite)->MoveFoePlane(BIG_MOVE_STEP);
			}
			else if(typeid(*(*ite)) == typeid(CFoePlaneMid)) {
				(*ite)->MoveFoePlane(MID_MOVE_STEP);
			}
			else if (typeid(*(*ite)) == typeid(CFoePlaneSma)) {
				(*ite)->MoveFoePlane(SMA_MOVE_STEP);
			}
			//判断是否出界
			if ((*ite)->m_y >= BACK_HEIGHT) {
				delete(*ite);//回收敌人飞机
				(*ite) = nullptr;
				ite=m_lstFoe.erase(ite);	//删除节点
				continue;
			}
		}
		ite++;
	}
}
