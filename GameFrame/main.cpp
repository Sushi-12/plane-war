#include"GameFrame.h"
#include<Windowsx.h>

//父类游戏壳的指针
CGameFrame* pGame = nullptr;
//声明的具体游戏窗口参数变量 
extern int wndWidth;
extern int wndHeight;
extern int wndPosX;
extern int wndPosY;
extern const TCHAR* wndTitle;



//3. 游戏运行 在回调函数中处理
//hwnd :窗口句柄，
// uMsg: 消息ID 等效于  msg.message
//wParam ,lParam : 消息携带的信息
LRESULT CALLBACK RunGame(_In_  HWND hwnd, _In_  UINT uMsg, _In_  WPARAM wParam, _In_  LPARAM lParam) {
	if (pGame->m_MsgMap.count(uMsg)) {	//消息ID在映射表中存在
		switch (pGame->m_MsgMap[uMsg].MsgType) {
		case EM_MOUSE: {
			//获取坐标点
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_MOUSE)(po);
		}
					 break;
		case EM_KEY: {
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_KEY)(wParam);
		}
					 break;
		case EM_CHAR: {

			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_CHAR)(wParam);
		}
					 break;
		case EM_WINDOW: {
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEM_WINDOW)(wParam, lParam);
		}
					 break;
		}
		//---------------------------------
		//重新绘制窗口，来保证及时刷新，在这里应当，我手动触发 WM_PAINT
		RECT rect{0,0,wndWidth,wndHeight};//定义矩形变量
		::InvalidateRect(pGame->m_hWnd,   //将那个窗口变为无效的
			&rect,						  //将窗口的哪部分变为无效的
			false);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);   //对于不关心的消息，由window默认的处理函数去处理
}





int main() {
	CGameFrame* CreateObject();//函数声明
	pGame = CreateObject();
	//初始化窗口
	pGame->InitGame(wndWidth, wndHeight, wndPosX, wndPosY, wndTitle);
	//主函数的循环，循环退出，程序则退出
	while (!pGame->GetQuit()) {
		Sleep(1000);
	}
	//回收资源
	delete pGame;
	pGame = nullptr;
	return 0;
}